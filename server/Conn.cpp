#include <iostream>
#include <string>
#include "Conn.h"

/*#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASSWORD "rootpwd"
#define DB_DBNAME "test"*/

#define DB_HOST "db"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASSWORD "rootpwd"
#define DB_DBNAME "test"

using namespace std;

Conn::Conn() {
  mysql = mysql_init(NULL);

  if (!mysql) {
    cout << "Error:" << mysql_error(mysql);
    exit(1);
  }
}

Conn::~Conn() {
  if (mysql) {
    mysql_close(mysql);
  }
}

bool Conn::initDB() {

  mysql = mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASSWORD, DB_DBNAME, DB_PORT, NULL, 0);

  if (!mysql) {
    cout << "Connect Error: " << mysql_error(mysql);
    exit(1);
  }

  return true;
}

/*bool Conn::getUserInfo(string user, string password, MYSQL_ROW *ret) {
  string sql = "SELECT * FROM users where name = '" + user + "' and password = '" + password + "'";

  if (mysql_query(mysql, sql.c_str())) {
    cout << "Query Error: " << mysql_error(mysql);
    return false;
  }

  MYSQL_RES *result = mysql_store_result(mysql);

  if (result) {
    unsigned int num_rows = mysql_num_rows(result);

    if (num_rows == 1) {
      MYSQL_ROW row = mysql_fetch_row(result);
      ret = *row;
      return true;
    } else {
      return false;
    }
  } else {
    cout << "Result Not Found";
    return false;
  }
}*/

/*
bool Conn::exeSQL(string sql) {
  //mysql_query()执行成功返回0,执行失败返回非0值。
  if (mysql_query(mysql, sql.c_str())) {
    cout << "Query Error: " << mysql_error(mysql);
    return false;
  }

  result = mysql_store_result(mysql);

  if (result) {
    //获取结果集中总共的字段数，即列数
    int num_fields = mysql_num_fields(result);
    unsigned int num_rows = mysql_num_rows(result);

    for (unsigned int i = 0; i < num_rows; i++) {
      row = mysql_fetch_row(result);
      if (!row) {
        break;
      }

      for (int j = 0; j < num_fields; j++) {
        cout << row[j] << "\t\t";
      }
      cout << endl;
    }
  } else {
    //代表执行的是update,insert,delete类的非查询语句
    if (mysql_field_count(mysql) == 0) {
      // 返回update,insert,delete影响的行数
      unsigned long long num_rows = mysql_affected_rows(mysql);

      return num_rows;
    } else {
      cout << "Get result error: " << mysql_error(mysql);
      return false;
    }
  }

  return true;
}*/
