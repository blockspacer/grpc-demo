
#include "UserEntity.h"

#include <utility>

UserEntity::UserEntity(Conn *conn, string userName, string password) {
  db = conn;
  this->userName = userName;
  this->password = password;
  initType = INITIALIZE_USER_PASSWORD;
}

UserEntity::UserEntity(Conn *conn, unsigned int uid, LoginInfo *loginInfo) {
  db = conn;
  this->uid = uid;
  this->loginInfo = loginInfo;
  initType = INITIALIZE_UID;
}

int UserEntity::doRegister() {
  // 检查账户合法性
  if (initType == INITIALIZE_USER_PASSWORD && validateAccountInfo()) {
    // 检查用户名是否存在
    string selectStmt = "select * from users where `name` = ?";
    unsigned long queryParamLength = userName.length();
    MYSQL_BIND queryBind[1];
    memset(queryBind, 0, sizeof(queryBind));
    queryBind[0].buffer_type = MYSQL_TYPE_STRING;
    queryBind[0].buffer = (char *) userName.c_str();
    queryBind[0].buffer_length = FIELD_USERNAME_LENGTH;
    queryBind[0].is_null = 0;
    queryBind[0].length = &queryParamLength;
    if (db->execute(selectStmt, queryBind)) {
      unsigned int num = db->getQueryNum();
      if (num > 0) {
        return CODE_USER_EXIST;
      } else {
        string insertStmt = "insert into users (`name`, `password`)values(?,?)";
        unsigned long insertParamLength[2];
        MYSQL_BIND insertBind[2];
        memset(insertBind, 0, sizeof(insertBind));
        insertParamLength[0] = userName.length();
        insertBind[0].buffer_type = MYSQL_TYPE_STRING;
        insertBind[0].buffer = (char *) userName.c_str();
        insertBind[0].buffer_length = FIELD_USERNAME_LENGTH;
        insertBind[0].is_null = 0;
        insertBind[0].length = &insertParamLength[0];

        string e_password = encryptPassword(password);
        insertParamLength[1] = e_password.length();
        insertBind[1].buffer_type = MYSQL_TYPE_STRING;
        insertBind[1].buffer = (char *) e_password.c_str();
        insertBind[1].buffer_length = FIELD_PASSWORD_LENGTH;
        insertBind[1].is_null = 0;
        insertBind[1].length = &insertParamLength[1];
        if (db->execute(insertStmt, insertBind)) {
          num = db->getAffectedNum();
          if (num > 0) {
            return CODE_OK;
          } else {
            return CODE_DB_ERROR;
          }
        } else {
          return CODE_DB_ERROR;
        }
      }
    } else {
      return CODE_DB_ERROR;
    }
  } else {
    return CODE_INVALID_PARAMS;
  }
}

bool UserEntity::login(LoginInfo *loginInfo) {
  // 检查账户合法性
  if (initType == INITIALIZE_USER_PASSWORD && validateAccountInfo()) {
    // 取出用户密码，做B-crypt校验
    string selectStmt = "select password from users where `name` = ?";
    unsigned long queryParamLength = userName.length();
    MYSQL_BIND queryBind[1];
    memset(queryBind, 0, sizeof(queryBind));
    queryBind[0].buffer_type = MYSQL_TYPE_STRING;
    queryBind[0].buffer = (char *) userName.c_str();
    queryBind[0].buffer_length = FIELD_USERNAME_LENGTH;
    queryBind[0].is_null = 0;
    queryBind[0].length = &queryParamLength;
    if (db->execute(selectStmt, queryBind)) {
      char db_password[FIELD_USERNAME_LENGTH];
      unsigned long fetchPwdLength;
      MYSQL_BIND fetchBind[1];
      memset(fetchBind, 0, sizeof(fetchBind));
      fetchBind[0].buffer_type = MYSQL_TYPE_STRING;
      fetchBind[0].buffer = (char *) db_password;
      fetchBind[0].buffer_length = FIELD_PASSWORD_LENGTH;
      fetchBind[0].length = &fetchPwdLength;

      db->bindResult(fetchBind);
      int num = db->getQueryNum();
      if (num > 0) {
        // 取一行
        db->fetch();
        cout << "db_password length: " + to_string(fetchPwdLength) + ", content: " << db_password << endl;
        // 校验密码是否正确
        int ret = bcrypt_checkpw(password.c_str(), db_password);
        if (ret == 0) {
          refreshLoginInfo(loginInfo);
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool UserEntity::refreshLoginInfo(LoginInfo *loginInfo) {
  // 生成本次登录态凭证
  string token = genToken(loginInfo);
  // 同步登录态到DB
  // 先查一遍是否有登录态信息
  string selectStmt = "select null from session where uid = ?";
  int userId = atoi(uid.c_str());
  MYSQL_BIND queryBind[1];
  memset(queryBind, 0, sizeof(queryBind));
  queryBind[0].buffer_type = MYSQL_TYPE_LONG;
  queryBind[0].buffer = (char *)&userId;
  queryBind[0].is_null = 0;
  queryBind[0].length = 0;
  if (db->execute(selectStmt, queryBind)) {
    int num = db->getQueryNum();
    // 有登录态信息则更新
    if (num > 0) {
//      string updateStmt = "update session set loginTime=?,ip=?,channel=?,token=? where uid = ?";
//      MYSQL_BIND updateBind[5];
//      memset(updateBind, 0, sizeof(updateBind));

      return true;
    } else {  // 没登录态信息则插入
//      string insertStmt = "insert into session (uid,loginTime,ip,channel,token)values(?,?,?,?,?)";
    }
  } else {
    return false;
  }
}

bool UserEntity::checkLogin() {
  return true;
}

string UserEntity::encryptPassword(string pwd) {
  char salt[BCRYPT_HASHSIZE];
  char hash[BCRYPT_HASHSIZE];
  // 工作因子，默认为10
  bcrypt_gensalt(10, salt);
  bcrypt_hashpw(pwd.c_str(), salt, hash);
  return hash;
}

string UserEntity::genToken(LoginInfo *loginInfo) {
  string rawStr = uid + "|some salt*&@#|" + loginInfo->loginTime + "|" + loginInfo->channel + "|" + loginInfo->ip;
  // 简单做一次b-crypt
  char salt[BCRYPT_HASHSIZE];
  char hash[BCRYPT_HASHSIZE];
  bcrypt_gensalt(10, salt);
  bcrypt_hashpw(rawStr.c_str(), salt, hash);
  // 再做一次md5
  // 再加一次盐
  string saltedHash = "salt-again@{}@#}" + hash;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) saltedHash.c_str(), strlen(saltedHash));
  string md5_str(iMD5.ToString());
  return md5_str;
}

bool UserEntity::validateAccountInfo() {
  return regex_match(userName, regex("\\w+")) && userName.length() < FIELD_USERNAME_LENGTH &&
    regex_match(password, regex("\\S+")) && password.length() < FIELD_PASSWORD_BEFORE_ENCRYPT_LENGTH;
}
