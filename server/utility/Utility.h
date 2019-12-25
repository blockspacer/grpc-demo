//
// Created by Zhong Yu on 2019/12/24.
//

#ifndef GRPC_DEMO_UTILITY_H
#define GRPC_DEMO_UTILITY_H

#include <iostream>
#include <sstream>

using namespace std;

class Utility {
public:
  static string parseIpString(string ipString);
  static string getTimestamp();

  static string security(string input);
};


#endif //GRPC_DEMO_UTILTY_H
