
#ifndef GRPC_DEMO_USERENTITY_H
#define GRPC_DEMO_USERENTITY_H

#include <iostream>

//#include "../encryption/Md5.h"

using namespace std;

struct LoginInfo {
  string loginTime;
  string ip;
  string channel;
  string token = "";
};

class UserEntity {
public:
  string uid = 0;
  string userName;
  LoginInfo loginInfo;

  static int doRegister(string username, string password);

  explicit UserEntity(string userName);

  explicit UserEntity(unsigned int uid);

  bool validatePassword(string password);

  bool validateLoginInfo(LoginInfo info);

  bool refreshLoginInfo(LoginInfo info);
private:
  bool loadUserInfo();
  bool loadLoginInfo();

  string encryptPassword(string pwd);
  string genToken(string uid, string ts, string ip, string channel);
};


#endif //GRPC_DEMO_USERENTITY_H
