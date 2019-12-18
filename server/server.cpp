#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "protos/server.grpc.pb.h"

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
using UserAgent::UserService;

// Logic and data behind the server's behavior.
class UserServerServiceImpl final : public UserService::Service {
  Status Login(ServerContext *context, const LoginRequest *request,
               LoginResponse *reply) override {
    std::string user = request->user();
    reply->set_ret_code(0);
    reply->set_uid(1000);
    reply->set_token(user);
    return Status::OK;
  }

  Status CheckLogin(ServerContext *context, const CheckLoginRequest *request,
                    CheckLoginResponse *reply) override {
    return Status::OK;
  }

  Status Register(ServerContext *context, const RegisterRequest *request,
                  RegisterResponse *reply) override {
    return Status::OK;
  }
};

void RunServer() {
    std::string server_address("0.0.0.0:9090");
    UserServerServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}