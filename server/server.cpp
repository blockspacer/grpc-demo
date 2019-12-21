#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "protos/server.grpc.pb.h"

#include "Conn.h"

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

class UserServerServiceImpl final : public UserService::Service {
public:
  UserServerServiceImpl() {
    //连接数据库
    bool conn = db.initDB();

    if (!conn) {
      cout << "connect fails\n";
    } else {
      cout << "Connect database successfully" << endl;
    }
  }

private:
  Conn db;

  Status Login(ServerContext *context, const LoginRequest *request,
               LoginResponse *reply) override {
    std::string userName = request->user();
    std::string password = request->password();
    reply->set_ret_code(0);
    reply->set_uid(1000);
    reply->set_token(userName);

    //根据用户传输的
    string sql = "SELECT * FROM users where name = '" + userName + "' and password = '" + password + "'";

    if (mysql_query(db.mysql, sql.c_str())) {
      cout << "Query Error: " << mysql_error(db.mysql);
      return Status::CANCELLED;
    }

    MYSQL_RES *result = mysql_store_result(db.mysql);

    if (result) {
      unsigned int num_rows = mysql_num_rows(result);
      cout << num_rows << endl;
    } else {
      cout << "fail to query" << endl;
    }
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
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr <Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main() {
  RunServer();

  return 0;
}