
#include "UserService.h"

UserService::UserService() {
  //连接数据库
  bool conn = db.initDB();

  if (!conn) {
    cout << "connect fails\n";
  } else {
    cout << "Connect database successfully" << endl;
  }
}

Status UserService::Login(ServerContext *context, const LoginRequest *request, LoginResponse *reply) {
  const string userName = Utility::security(request->user());
  const string password = Utility::security(request->password());
  const string channel = Utility::security(request->channel());
  const string ip = Utility::parseIpString(context->peer());
  string timestamp = Utility::getTimestamp();

  auto *user = new UserEntity(&db, userName, password);
  LoginInfo loginInfo;
  loginInfo.channel = channel;
  loginInfo.ip = ip;
  loginInfo.loginTime = timestamp;

  // 执行登录操作
  if (user->login(&loginInfo)) {
    reply->set_ret_code(0);
    return Status::OK;
  } else { // 密码不正确
    reply->set_ret_code(1);
    return Status::OK;
  }
  return Status::OK;
}

Status UserService::CheckLogin(ServerContext *context, const CheckLoginRequest *request, CheckLoginResponse *reply) {
  /*const string uid = Utility::security(request->uid());
  const string token = Utility::security(request->token());
  const string ip = Utility::parseIpString(context->peer());

  string timestamp = Utility::getTimestamp();

  auto *user = new UserEntity(&db, uid);

  LoginInfo loginInfo;

  loginInfo.ip = ip;
  loginInfo.token = ip;

  // 检查登录态
  if (user->validateLoginInfo(loginInfo)) {
    reply->set_ret_code(0);
    reply->set_channel(user->loginInfo.channel);
    return Status::OK;
  } else {  // 没有任何一个tab的有效登录态
    reply->set_ret_code(1);
    return Status::OK;
  }*/
  return Status::OK;
}

Status UserService::Register(ServerContext *context, const RegisterRequest *request, RegisterResponse *reply) {
  const string user = Utility::security(request->user());
  const string password = Utility::security(request->password());

  auto userEntity = new UserEntity(&db, user, password);

  int result = userEntity->doRegister();
  switch(result) {
    case CODE_OK:
      reply->set_ret_code(0);
      return Status::OK;
    case CODE_INVALID_PARAMS:  // 用户名或密码不符合要求
      reply->set_ret_code(1);
      return Status::OK;
    case CODE_USER_EXIST:  // 用户名已存在
      reply->set_ret_code(2);
      return Status::OK;
    default:
      return Status::CANCELLED;
  }
}
