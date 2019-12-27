#include <iostream>
#include <grpc++/grpc++.h>

#include "service/UserService.h"

using grpc::Server;
using grpc::ServerBuilder;

using namespace std;

int main() {
  string server_address("0.0.0.0:9090");
  UserService service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << endl;
  server->Wait();

  return 0;
}
