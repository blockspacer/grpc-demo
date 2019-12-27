
#include "UserEntity.h"

#include <utility>

UserEntity::UserEntity(Conn *conn, string userName, string password) {
  db = conn;
  this->userName = userName;
  this->password = password;
  initType = INITIALIZE_USER_PASSWORD;
}

UserEntity::UserEntity(Conn *conn, unsigned int uid) {
  db = conn;
  this->uid = uid;
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

bool UserEntity::login(LoginInfo *info) {
  // 检查账户合法性
  if (initType == INITIALIZE_USER_PASSWORD && validateAccountInfo()) {
    // 取出用户密码，做B-crypt校验
    string selectStmt = "select id,password from users where `name` = ?";
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
      unsigned long fetchPwdLength[2];
      MYSQL_BIND fetchBind[2];
      memset(fetchBind, 0, sizeof(fetchBind));
      fetchBind[0].buffer_type = MYSQL_TYPE_LONG;
      fetchBind[0].buffer = (char *) &uid;
      fetchBind[0].length = &fetchPwdLength[0];

      fetchBind[1].buffer_type = MYSQL_TYPE_STRING;
      fetchBind[1].buffer = (char *) db_password;
      fetchBind[1].buffer_length = FIELD_PASSWORD_LENGTH;
      fetchBind[1].length = &fetchPwdLength[1];

      db->bindResult(fetchBind);
      int num = db->getQueryNum();
      if (num > 0) {
        // 取一行
        db->fetch();
        // 校验密码是否正确
        int ret = bcrypt_checkpw(password.c_str(), db_password);
        if (ret == 0) {
          refreshLoginInfo(info);
          return true;
        } else {
          cout << "Failed to verify password" << endl;
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

bool UserEntity::refreshLoginInfo(LoginInfo *info) {
  // 生成本次登录态凭证
  string token = genToken(info);
  // 同步登录态到DB
  // 先查一遍是否有登录态信息
  string selectStmt = "select loginTime from session where uid = ?";
  MYSQL_BIND queryBind[1];
  memset(queryBind, 0, sizeof(queryBind));
  queryBind[0].buffer_type = MYSQL_TYPE_LONG;
  queryBind[0].buffer = (char *) &uid;
  queryBind[0].is_null = 0;
  queryBind[0].length = 0;
  if (db->execute(selectStmt, queryBind)) {
    int num = db->getQueryNum();
    // 有登录态信息则更新
    if (num > 0) {
      string updateStmt = "update session set loginTime=?,ip=?,channel=?,token=? where uid = ?";
      unsigned long updateParamLength[5];
      MYSQL_BIND updateBind[5];
      memset(updateBind, 0, sizeof(updateBind));

      updateParamLength[0] = info->loginTime.length();
      updateBind[0].buffer_type = MYSQL_TYPE_STRING;
      updateBind[0].buffer = (char *) info->loginTime.c_str();
      updateBind[0].buffer_length = FIELD_USERNAME_LENGTH;
      updateBind[0].is_null = 0;
      updateBind[0].length = &updateParamLength[0];

      updateParamLength[1] = info->ip.length();
      updateBind[1].buffer_type = MYSQL_TYPE_STRING;
      updateBind[1].buffer = (char *) info->ip.c_str();
      updateBind[1].buffer_length = FIELD_USERNAME_LENGTH;
      updateBind[1].is_null = 0;
      updateBind[1].length = &updateParamLength[1];

      updateParamLength[2] = info->channel.length();
      updateBind[2].buffer_type = MYSQL_TYPE_STRING;
      updateBind[2].buffer = (char *) info->channel.c_str();
      updateBind[2].buffer_length = FIELD_USERNAME_LENGTH;
      updateBind[2].is_null = 0;
      updateBind[2].length = &updateParamLength[2];

      updateParamLength[3] = token.length();
      updateBind[3].buffer_type = MYSQL_TYPE_STRING;
      updateBind[3].buffer = (char *) token.c_str();
      updateBind[3].buffer_length = FIELD_USERNAME_LENGTH;
      updateBind[3].is_null = 0;
      updateBind[3].length = &updateParamLength[3];

      updateBind[4].buffer_type = MYSQL_TYPE_LONG;
      updateBind[4].buffer = (char *)&uid;
      updateBind[4].is_null = 0;
      updateBind[4].length = 0;

      if (db->execute(updateStmt, updateBind)) {
        num = db->getAffectedNum();
        if (num > 0) {
          loginInfo = info;
          loginInfo->token = token;
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {  // 没登录态信息则插入
      string insertStmt = "insert into session (uid,loginTime,ip,channel,token)values(?,?,?,?,?)";
      unsigned long insertParamLength[5];
      MYSQL_BIND insertBind[5];
      memset(insertBind, 0, sizeof(insertBind));

      insertBind[0].buffer_type = MYSQL_TYPE_LONG;
      insertBind[0].buffer = (char *)&uid;
      insertBind[0].is_null = 0;
      insertBind[0].length = 0;

      insertParamLength[1] = info->loginTime.length();
      insertBind[1].buffer_type = MYSQL_TYPE_STRING;
      insertBind[1].buffer = (char *) info->loginTime.c_str();
      insertBind[1].buffer_length = FIELD_USERNAME_LENGTH;
      insertBind[1].is_null = 0;
      insertBind[1].length = &insertParamLength[1];

      insertParamLength[2] = info->ip.length();
      insertBind[2].buffer_type = MYSQL_TYPE_STRING;
      insertBind[2].buffer = (char *) info->ip.c_str();
      insertBind[2].buffer_length = FIELD_USERNAME_LENGTH;
      insertBind[2].is_null = 0;
      insertBind[2].length = &insertParamLength[2];

      insertParamLength[3] = info->channel.length();
      insertBind[3].buffer_type = MYSQL_TYPE_STRING;
      insertBind[3].buffer = (char *) info->channel.c_str();
      insertBind[3].buffer_length = FIELD_USERNAME_LENGTH;
      insertBind[3].is_null = 0;
      insertBind[3].length = &insertParamLength[3];

      insertParamLength[4] = token.length();
      insertBind[4].buffer_type = MYSQL_TYPE_STRING;
      insertBind[4].buffer = (char *) token.c_str();
      insertBind[4].buffer_length = FIELD_PASSWORD_LENGTH;
      insertBind[4].is_null = 0;
      insertBind[4].length = &insertParamLength[4];

      if (db->execute(insertStmt, insertBind)) {
        num = db->getAffectedNum();
        if (num > 0) {
          loginInfo = info;
          loginInfo->token = token;
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
}

bool UserEntity::checkLogin(LoginInfo *info, const char *ts) {
  // 获取当前用户登录态信息
  string selectStmt = "select loginTime,ip,channel,token from session where `uid` = ?";
  MYSQL_BIND queryBind[1];
  memset(queryBind, 0, sizeof(queryBind));
  queryBind[0].buffer_type = MYSQL_TYPE_LONG;
  queryBind[0].buffer = (char *) &uid;
  queryBind[0].is_null= 0;
  queryBind[0].length= 0;
  if (db->execute(selectStmt, queryBind)) {
    char db_loginTime[FIELD_USERNAME_LENGTH];
    char db_ip[FIELD_USERNAME_LENGTH];
    char db_channel[FIELD_PASSWORD_LENGTH];
    char db_token[FIELD_PASSWORD_LENGTH];
    unsigned long fetchLength[4];
    MYSQL_BIND fetchBind[4];
    memset(fetchBind, 0, sizeof(fetchBind));

    fetchBind[0].buffer_type = MYSQL_TYPE_STRING;
    fetchBind[0].buffer = (char *) db_loginTime;
    fetchBind[0].buffer_length = FIELD_USERNAME_LENGTH;
    fetchBind[0].length = &fetchLength[0];

    fetchBind[1].buffer_type = MYSQL_TYPE_STRING;
    fetchBind[1].buffer = (char *) db_ip;
    fetchBind[1].buffer_length = FIELD_USERNAME_LENGTH;
    fetchBind[1].length = &fetchLength[1];

    fetchBind[2].buffer_type = MYSQL_TYPE_STRING;
    fetchBind[2].buffer = (char *) db_channel;
    fetchBind[2].buffer_length = FIELD_PASSWORD_LENGTH;
    fetchBind[2].length = &fetchLength[2];

    fetchBind[3].buffer_type = MYSQL_TYPE_STRING;
    fetchBind[3].buffer = (char *) db_token;
    fetchBind[3].buffer_length = FIELD_PASSWORD_LENGTH;
    fetchBind[3].length = &fetchLength[3];

    db->bindResult(fetchBind);
    int num = db->getQueryNum();
    if (num > 0) {
      db->fetch();
      // 判断IP是否已变更
      if (info->ip != db_ip) {
        return false;
      }
      // 判断登录态是否已过期
      if (atoi(ts) - atoi(db_loginTime) > LOGIN_INFO_EXPIRE_TIME) {
        return false;
      }
      // 查询token是否匹配
      if (info->token != db_token) {
        return false;
      }
      // IP和token都匹配，登录态也没过期，则返回已登录的tab信息
      loginInfo = info;
      loginInfo->channel = db_channel;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

string UserEntity::encryptPassword(string pwd) {
  char salt[BCRYPT_HASHSIZE];
  char hash[BCRYPT_HASHSIZE];
  // 工作因子，默认为10
  bcrypt_gensalt(10, salt);
  bcrypt_hashpw(pwd.c_str(), salt, hash);
  return hash;
}

string UserEntity::genToken(LoginInfo *info) {
  string rawStr = to_string(uid) + "|some salt*&@#|" + info->loginTime + "|" + info->channel + "|" + info->ip;
  // 简单做一次b-crypt
  char salt[BCRYPT_HASHSIZE];
  char hash[BCRYPT_HASHSIZE];
  bcrypt_gensalt(6, salt);
  bcrypt_hashpw(rawStr.c_str(), salt, hash);
  // 再做一次md5
  // 再加一次盐
  string hashStr = hash;
  string saltedHash = "salt-again@{}@#}" + hashStr;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) saltedHash.c_str(), saltedHash.length());
  string md5_str(iMD5.ToString());
  return md5_str;
}

bool UserEntity::validateAccountInfo() {
  return regex_match(userName, regex("\\w+")) && userName.length() < FIELD_USERNAME_LENGTH &&
    regex_match(password, regex("\\S+")) && password.length() < FIELD_PASSWORD_BEFORE_ENCRYPT_LENGTH;
}
