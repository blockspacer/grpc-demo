
#include "UserEntity.h"

#include <utility>

UserEntity::UserEntity(Conn *conn, string userName) {
  this->db = conn;
  this->userName = userName;
}

UserEntity::UserEntity(Conn *conn, unsigned int uid) {
  this->db = conn;
  this->uid = uid;
}

int UserEntity::doRegister(string username, string password) {
  // 检查格式
  if (
      regex_match(username, regex("\\w+")) &&
      username.length() < 20 &&
      regex_match(password, regex("\\S+")) &&
      password.length() < 30
  ) {
    // 检查用户名是否存在
    string selectStmt = "select * from users where `name` = ?";
    unsigned long queryParamLength;
    MYSQL_BIND queryBind[1];
    memset(queryBind, 0, sizeof(queryBind));
    queryBind[0].buffer_type = MYSQL_TYPE_STRING;
    queryBind[0].buffer = (char *)username.c_str();
    queryBind[0].buffer_length = FIELD_USERNAME_LENGTH;
    queryBind[0].is_null = 0;
    queryBind[0].length = &queryParamLength;
    queryParamLength = username.length();
    if (db->execute(selectStmt, queryBind)) {
      unsigned int num = db->getQueryNum();
      if (num > 0) {
        return CODE_USER_EXIST;
      } else {
        string insertStmt = "insert into users (`name`, `password`)values(?,?)";
        unsigned long insertParamLength[2];
        MYSQL_BIND insertBind[2];
        memset(insertBind, 0, sizeof(insertBind));
        insertParamLength[0] = username.length();
        insertBind[0].buffer_type = MYSQL_TYPE_STRING;
        insertBind[0].buffer = (char *)username.c_str();
        insertBind[0].buffer_length = FIELD_USERNAME_LENGTH;
        insertBind[0].is_null = 0;
        insertBind[0].length = &insertParamLength[0];

        string e_password = encryptPassword(password);
        insertParamLength[1] = e_password.length();
        insertBind[1].buffer_type = MYSQL_TYPE_STRING;
        insertBind[1].buffer = (char *)e_password.c_str();
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

bool UserEntity::validatePassword(string password) {
  return true;
}

bool UserEntity::loadLoginInfo() {
  if (userName.length() > 0) {

  } else if (uid > 0) {

  }
  return false;
}

bool UserEntity::loadUserInfo() {
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

/*
string User::encryptPassword(string pwd) {
  string salt = "(NSD)*ve3";
  string rawStr = pwd + salt;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) rawStr.c_str(), strlen(rawStr.c_str()));
  string md5_str(iMD5.ToString());
  return md5_str;
}

string User::genToken(string uid, string ts, string ip, string channel) {
  string salt = "*^#$2e3e3";
  string rawStr = uid + salt + ts + ip + salt + channel;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) rawStr.c_str(), strlen(rawStr.c_str()));
  string md5_str(iMD5.ToString());
  return md5_str;
}*/
