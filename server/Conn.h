#ifndef GRPC_DEMO_CONN_H
#define GRPC_DEMO_CONN_H

#include <string>
#include "include/mysql.h"

using namespace std;

class Conn {
public:
  Conn();

  ~Conn();

  // mysql句柄
  MYSQL *mysql;

  bool initDB();

};


#endif //GRPC_DEMO_CONN_H
