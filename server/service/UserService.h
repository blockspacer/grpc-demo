
#ifndef GRPC_DEMO_USERSERVICE_H
#define GRPC_DEMO_USERSERVICE_H

#include <iostream>
#include "../mysql/Conn.h"

#include "protos/server.grpc.pb.h"
#include <grpc++/grpc++.h>

#include "../utilty/Utilty.h"

using namespace std;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using UserAgent::LoginRequest;
using UserAgent::LoginResponse;
using UserAgent::CheckLoginRequest;
using UserAgent::CheckLoginResponse;
using UserAgent::RegisterRequest;
using UserAgent::RegisterResponse;
using UserAgent::User;

class UserService final : public User::Service {
public:
  UserService();

private:
  Conn db;

  Status Login(ServerContext *context, const LoginRequest *request, LoginResponse *reply) override;
  Status CheckLogin(ServerContext *context, const CheckLoginRequest *request, CheckLoginResponse *reply) override;
  Status Register(ServerContext *context, const RegisterRequest *request, RegisterResponse *reply) override;
};


#endif //GRPC_DEMO_USERSERVICE_H
