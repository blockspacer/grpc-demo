#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "src/protos/server.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using UserAgent::CheckLoginRequest;
using UserAgent::CheckLoginResponse;
using UserAgent::UserServer;

// Logic and data behind the server's behavior.
class UserServerServiceImpl final : public UserServer::Service {
    Status CheckLogin(ServerContext* context, const CheckLoginRequest* request,
                      CheckLoginResponse* reply) override {
        std::string prefix("Hello ");
        reply->set_retcode(0);
        reply->set_uid(1000);
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