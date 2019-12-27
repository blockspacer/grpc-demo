//
// Created by Zhong Yu on 2019/12/24.
//

#include "Utility.h"

string Utility::parseIpString(string ipString) {
  char *ipStr = new char[ipString.length() + 1];
  strcpy(ipStr, ipString.c_str());
  const char *delimiter = ":";
  strtok(ipStr, delimiter);
  return strtok(NULL, delimiter);
}

string Utility::getTimestamp() {
  chrono::time_point<chrono::system_clock,chrono::milliseconds> tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
  time_t timestamp =  tp.time_since_epoch().count();
  time(&timestamp);
  stringstream ss;
  ss << timestamp;
  return ss.str();
}

string Utility::security(string input) {
  // todo filter XSS attack
  return input;
}