#include <iostream>
#include <string>
#include "Conn.h"

//#define DB_HOST "127.0.0.1"
#define DB_HOST "db"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASSWORD "rootpwd"
#define DB_DBNAME "test"

using namespace std;

Conn::Conn() {
  initDB();
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
  // 检查db连接
  if (!connected && !initDB()) {
    cout << "Cannot connect to database" << endl;
    return false;
  }
  // 执行prepare
  if (mysql_stmt_prepare(stmt, statement.c_str(), statement.length())) {
    cout << "Fail to prepare statement" << endl;
    return false;
  }

  int param_count = mysql_stmt_param_count(stmt);

  // 绑定参数
  if (param_count > 0) {
    if (mysql_stmt_bind_param(stmt, parameters)) {
      cout << "Fail to bind parameters" << mysql_stmt_error(stmt) << endl;
      return false;
    }
  }

  if (mysql_stmt_execute(stmt)) {
    cout << "Fail to execute statement" << endl;
    cout << mysql_stmt_error(stmt) << endl;
    return false;
  }
  return true;
}

int Conn::getQueryNum() {
  if (mysql_stmt_store_result(stmt)) {
    cout << "Fail to fetch result" << endl;
    return false;
  }
  return mysql_stmt_num_rows(stmt);
}

int Conn::getAffectedNum() {
  return mysql_stmt_affected_rows(stmt);
}

bool Conn::bindResult(MYSQL_BIND *result) {
  if (mysql_stmt_bind_result(stmt, result)) {
    cout << "Fail to bind result" << endl;
    return false;
  }
  return true;
}

bool Conn::fetch() {
  return mysql_stmt_fetch(stmt);
}

bool Conn::initDB() {
  if (connected) {
    return true;
  }

  mysql = mysql_init(NULL);
  stmt = mysql_stmt_init(mysql);

  if (!stmt) {
    cout << "Error:" << mysql_error(mysql);
    return false;
  }

  mysql = mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASSWORD, DB_DBNAME, DB_PORT, NULL, 0);

  if (!mysql) {
    cout << "Fail to connect database" << endl;
    return false;
  } else {
    connected = true;
    return true;
  }
}
