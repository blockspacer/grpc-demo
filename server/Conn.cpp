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