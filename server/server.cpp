#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <sstream>

#include <grpc++/grpc++.h>

#include "protos/server.grpc.pb.h"

#include "Conn.h"
#include "Md5.h"

#define EXPIRETIME 1800 // 登录态过期时间

using namespace std;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using UserAgent::LoginRequest;
using UserAgent::LoginResponse;
using UserAgent::CheckLoginRequest;
using UserAgent::CheckLoginResponse;
using UserAgent::RegisterRequest;
using UserAgent::RegisterResponse;
using UserAgent::UserService;

string getTimestamp();
string genToken(string uid, string ts, string ip, string channel);
string parseIpString(string ipString);
string encryptPassword(string pwd);
string security(string input);

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
    const string userName = security(request->user());
    const string password = security(request->password());
    const string channel = security(request->channel());
    const string ip = parseIpString(context->peer());
    string timestamp = getTimestamp();

    string e_password = encryptPassword(password);
    //根据用户传输的账户密码，判断是否
    string sql = "SELECT * FROM users where name = '" + userName + "' and password = '" + e_password + "'";

    if (mysql_query(db.mysql, sql.c_str())) {
      cout << "Query Error: " << mysql_error(db.mysql);
      return Status::CANCELLED;
    }

    MYSQL_RES *result = mysql_store_result(db.mysql);

    if (result) {
      unsigned int num_rows = mysql_num_rows(result);
      if (num_rows > 0) {
        // 获取UID
        MYSQL_ROW row = mysql_fetch_row(result);
        string uid = row[0];
        reply->set_ret_code(0);
        reply->set_uid(atoi(uid.c_str()));
        string token = genToken(uid, timestamp, ip, channel);
        reply->set_token(token);
        // 保存登录态
        string sql2 = "INSERT INTO session (`uid`, `loginTime`, `ip`, `channel`, `token`)VALUES("
              "'" + uid + "',"
              "'" + timestamp + "',"
              "'" + ip + "',"
              "'" + channel + "',"
              "'" + token + "'"
              ") ON DUPLICATE KEY UPDATE "
              "`loginTime` = '" + timestamp + "',"
              "`ip` = '" + ip + "',"
              "`channel` = '" + channel + "',"
              "`token` = '" + token + "'";
        if (mysql_query(db.mysql, sql2.c_str())) {
          cout << "Update Login Info Error: " << mysql_error(db.mysql);
          return Status::CANCELLED;
        }
        num_rows = mysql_affected_rows(db.mysql);
        if (num_rows <= 0) {
          cout << "Write Login Info Fail: " << mysql_error(db.mysql);
          return Status::CANCELLED;
        } else {
          return Status::OK;
        }
      } else {
        reply->set_ret_code(1);
        return Status::OK;
      }
    } else {
      cout << "fail to query" << endl;
      return Status::CANCELLED;
    }
    return Status::OK;
  }

  Status CheckLogin(ServerContext *context, const CheckLoginRequest *request,
                    CheckLoginResponse *reply) override {
    const string uid = security(request->uid());
    const string token = security(request->token());
    const string ip = parseIpString(context->peer());

    string timestamp = getTimestamp();
    // 检查登录态是否合法
    string sql = "SELECT * FROM session WHERE `uid` = '" + uid + "'";
    if (mysql_query(db.mysql, sql.c_str())) {
      cout << "Query Error: " << mysql_error(db.mysql);
      return Status::CANCELLED;
    }

    MYSQL_RES *result = mysql_store_result(db.mysql);

    if (result) {
      unsigned int num_rows = mysql_num_rows(result);
      if (num_rows <= 0) {
        cout << "No Session Info[" + uid + "]" << endl;
        reply->set_ret_code(1);
        return Status::OK;
      }
      MYSQL_ROW row = mysql_fetch_row(result);
      string db_loginTime = row[1];
      string db_ip = row[2];
      string db_channel = row[3];
      string db_token = row[4];
      // 判断登录态是否超时，默认30分钟
      if (atoi(timestamp.c_str()) - atoi(db_loginTime.c_str()) > EXPIRETIME) {
        cout << "Session expired" << endl;
        reply->set_ret_code(1);
        return Status::OK;
      }
      // 判断ip是否已更换
      if (ip != db_ip) {
        cout << "IP changed" << endl;
        reply->set_ret_code(1);
        return Status::OK;
      }
      // 验证token一致性，返回已登录的tab
      if (token == db_token) {
        reply->set_ret_code(0);
        reply->set_channel(db_channel);
        return Status::OK;
      } else {
        reply->set_ret_code(1);
        return Status::OK;
      }
    } else {
      cout << "Query Login Info Error" << endl;
      return Status::CANCELLED;
    }
    return Status::OK;
  }

  Status Register(ServerContext *context, const RegisterRequest *request,
                  RegisterResponse *reply) override {
    const string user = security(request->user());
    const string password = security(request->password());
    // 检查用户名是否存在
    string sql = "SELECT * FROM users WHERE `name` = '" + user + "'";
    if (mysql_query(db.mysql, sql.c_str())) {
      cout << "Query User Name Error: " << mysql_error(db.mysql);
      return Status::CANCELLED;
    }
    MYSQL_RES *result = mysql_store_result(db.mysql);
    if (result) {
      unsigned int num_rows = mysql_num_rows(result);
      if (num_rows > 0) {
        cout << "User Name Exist" << endl;
        reply->set_ret_code(2);
        return Status::OK;
      }
      string e_password = encryptPassword(password);
      string sql2 = "INSERT INTO users (`name`, `password`)VALUES("
                    "'" + user + "',"
                    "'" + e_password + "'"
                    ")";
      if (mysql_query(db.mysql, sql2.c_str())) {
        cout << "Insert User Error: " << mysql_error(db.mysql);
        return Status::CANCELLED;
      }
      num_rows = mysql_affected_rows(db.mysql);
      if (num_rows <= 0) {
        cout << "Register User Fail: " << mysql_error(db.mysql);
        return Status::CANCELLED;
      } else {
        return Status::OK;
      }
    }
    return Status::OK;
  }
};

string encryptPassword(string pwd) {
  string salt = "(NSD)*ve3";
  string rawStr = pwd + salt;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) rawStr.c_str(), strlen(rawStr.c_str()));
  string md5_str(iMD5.ToString());
  return md5_str;
}

string genToken(string uid, string ts, string ip, string channel) {
  string salt = "*^#$2e3e3";
  string rawStr = uid + salt + ts + ip + salt + channel;
  MD5 iMD5;
  iMD5.GenerateMD5((unsigned char *) rawStr.c_str(), strlen(rawStr.c_str()));
  string md5_str(iMD5.ToString());
  return md5_str;
}

string getTimestamp()
{
  chrono::time_point<chrono::system_clock,chrono::milliseconds> tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
  time_t timestamp =  tp.time_since_epoch().count();
  time(&timestamp);
  stringstream ss;
  ss << timestamp;
  return ss.str();
}

string parseIpString(string ipString) {
  char *ipStr = new char[ipString.length() + 1];
  strcpy(ipStr, ipString.c_str());
  const char *delimiter = ":";
  strtok(ipStr, delimiter);
  return strtok(NULL, delimiter);
}

string security(string input) {
  // todo filter XSS attack
  // todo filter SQL inject
  return input;
}

void RunServer() {
  string server_address("0.0.0.0:9090");
  UserServerServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << endl;
  server->Wait();
}

int main() {
  RunServer();

  return 0;
}
