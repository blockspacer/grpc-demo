
#ifndef GRPC_DEMO_USERENTITY_H
#define GRPC_DEMO_USERENTITY_H

#define CODE_OK 0
#define CODE_INVALID_PARAMS 1
#define CODE_USER_EXIST 2
#define CODE_DB_ERROR 100

#define FIELD_USERNAME_LENGTH 20
#define FIELD_PASSWORD_LENGTH 64

#include <iostream>
#include <regex>

#include "../encryption/bcrypt/bcrypt.h"
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
  LoginInfo loginInfo;

  int doRegister(string username, string password);

  explicit UserEntity(Conn *conn, string userName);

  explicit UserEntity(Conn *conn, unsigned int uid);

  bool validatePassword(string password);

  bool validateLoginInfo(LoginInfo info);

  bool refreshLoginInfo(LoginInfo info);

  static string encryptPassword(string pwd);
private:
  Conn *db;

  bool loadUserInfo();
  bool loadLoginInfo();

  string genToken(string uid, string ts, string ip, string channel);
};


#endif //GRPC_DEMO_USERENTITY_H
