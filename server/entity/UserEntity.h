
#ifndef GRPC_DEMO_USERENTITY_H
#define GRPC_DEMO_USERENTITY_H

#define CODE_OK 0
#define CODE_INVALID_PARAMS 1
#define CODE_USER_EXIST 2
#define CODE_DB_ERROR 100

#define FIELD_USERNAME_LENGTH 20
#define FIELD_PASSWORD_BEFORE_ENCRYPT_LENGTH 30
#define FIELD_PASSWORD_LENGTH 64

#define INITIALIZE_NONE 0
#define INITIALIZE_USER_PASSWORD 1
#define INITIALIZE_UID 2

#include <iostream>
#include <regex>
#include <string>

#include "../encryption/bcrypt/bcrypt.h"
#include "../encryption/md5/Md5.h"
#include "../mysql/Conn.h"

using namespace std;

struct LoginInfo {
  string loginTime;
  string ip;
  string channel;
  string token = "";
};

class UserEntity {
public:
  unsigned int uid = 0;
  string userName;
  string password;
  LoginInfo *loginInfo;
  int initType = INITIALIZE_NONE;

  explicit UserEntity(Conn *conn, string userName, string password);

  explicit UserEntity(Conn *conn, unsigned int uid, LoginInfo *loginInfo);

  int doRegister();

  bool login(LoginInfo *loginInfo);

  bool checkLogin();

  static string encryptPassword(string pwd);
private:
  Conn *db;

  bool validateAccountInfo();

  bool refreshLoginInfo(LoginInfo *loginInfo);

  string genToken(LoginInfo *loginInfo);
};


#endif //GRPC_DEMO_USERENTITY_H
