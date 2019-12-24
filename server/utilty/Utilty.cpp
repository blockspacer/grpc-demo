//
// Created by Zhong Yu on 2019/12/24.
//

#include "Utilty.h"

string Utilty::parseIpString(string ipString) {
  char *ipStr = new char[ipString.length() + 1];
  strcpy(ipStr, ipString.c_str());
  const char *delimiter = ":";
  strtok(ipStr, delimiter);
  return strtok(NULL, delimiter);
}

string Utilty::getTimestamp() {
  chrono::time_point<chrono::system_clock,chrono::milliseconds> tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
  time_t timestamp =  tp.time_since_epoch().count();
  time(&timestamp);
  stringstream ss;
  ss << timestamp;
  return ss.str();
}

template <class T>
T Utilty::security(T &input) {
  // todo filter XSS attack
  // todo filter SQL inject
  return input;
}