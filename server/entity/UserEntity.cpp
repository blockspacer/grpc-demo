
#include "UserEntity.h"

UserEntity::UserEntity(string userName) {
  this->userName = userName;
}

bool UserEntity::loadLoginInfo() {
  return true;
}

bool UserEntity::loadUserInfo() {
  return true;
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
