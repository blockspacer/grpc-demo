
#include "../entity/UserEntity.h"
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
  const string userName = Utilty::security(request->user());
  const string password = Utilty::security(request->password());
  const string channel = Utilty::security(request->channel());
  const string ip = Utilty::parseIpString(context->peer());
  string timestamp = Utilty::getTimestamp();

  auto *user = new UserEntity(userName);
  LoginInfo loginInfo;
  loginInfo.channel = channel;
  loginInfo.ip = ip;
  loginInfo.loginTime = timestamp;

  // 验密正确则执行登录态刷新操作
  if (user->validatePassword(password) && user->refreshLoginInfo(loginInfo)) {
    reply->set_ret_code(0);
    reply->set_uid(user->uid);
    reply->set_token(user->loginInfo.token);
    return Status::OK;
  } else { // 密码不正确
    reply->set_ret_code(1);
    return Status::OK;
  }
}

Status UserService::CheckLogin(ServerContext *context, const CheckLoginRequest *request, CheckLoginResponse *reply) {
  const string uid = Utilty::security(request->uid());
  const string token = Utilty::security(request->token());
  const string ip = Utilty::parseIpString(context->peer());

  string timestamp = Utilty::getTimestamp();

  auto *user = new UserEntity(uid);

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
  }
}

Status UserService::Register(ServerContext *context, const RegisterRequest *request, RegisterResponse *reply) {
  const string user = Utilty::security(request->user());
  const string password = Utilty::security(request->password());

  int result = UserEntity::doRegister(user, password);
  switch(result) {
    case 0:
      reply->set_ret_code(0);
      return Status::OK;
    case 1:  // 密码复杂度不够
      reply->set_ret_code(1);
      return Status::OK;
    case 2:  // 用户名已存在
      reply->set_ret_code(2);
      return Status::OK;
    default:
      return Status::CANCELLED;
  }
}