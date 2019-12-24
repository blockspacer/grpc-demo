#ifndef GRPC_DEMO_CONN_H
#define GRPC_DEMO_CONN_H

#include <string>
//#include "include/mysql.h"
#include "macos/include/mysql.h"

using namespace std;

class Conn {
public:
  Conn();

  ~Conn();

  bool execute(const string& statement, MYSQL_BIND *parameters);

  // mysql句柄
  MYSQL *mysql;

  // prepared statement句柄
  MYSQL_STMT *stmt;

  bool initDB();
};


#endif //GRPC_DEMO_CONN_H
