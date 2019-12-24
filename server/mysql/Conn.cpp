#include <iostream>
#include <string>
#include "Conn.h"

#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASSWORD "rootpwd"
#define DB_DBNAME "test"

using namespace std;

template <class T>
int getArrayLen(T &array)
{
  return (sizeof(array) / sizeof(MYSQL_BIND));
}

Conn::Conn() {
  mysql = mysql_init(NULL);
  stmt = mysql_stmt_init(mysql);

  if (!stmt) {
    cout << "Error:" << mysql_error(mysql);
    exit(1);
  }
}

Conn::~Conn() {
  if (stmt) {
    mysql_stmt_close(stmt);
  }
  if (mysql) {
    mysql_close(mysql);
  }
}

bool Conn::execute(const string& statement, MYSQL_BIND *parameters) {
  // 执行prepare
  if (mysql_stmt_prepare(stmt, statement.c_str(), statement.length())) {
    cout << "Fail to prepare statement" << endl;
    return false;
  }
  // 绑定参数
  if (getArrayLen(parameters) > 0 && mysql_stmt_bind_param(stmt, parameters)) {
    cout << "Fail to bind parameters" << endl;
    return false;
  }
  if (mysql_stmt_execute(stmt)) {
    cout << "Fail to execute statement" << endl;
    return false;
  }
}

bool Conn::initDB() {

  mysql = mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASSWORD, DB_DBNAME, DB_PORT, NULL, 0);

  if (!mysql) {
    cout << "Connect Error: " << mysql_error(mysql) << endl;
    exit(1);
  }

  return true;
}