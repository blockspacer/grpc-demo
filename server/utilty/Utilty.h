//
// Created by Zhong Yu on 2019/12/24.
//

#ifndef GRPC_DEMO_UTILTY_H
#define GRPC_DEMO_UTILTY_H

#include <iostream>
#include <sstream>

using namespace std;

class Utilty {
public:
  static string parseIpString(string ipString);
  static string getTimestamp();

  template <class T>
  static T security(T &input);
};


#endif //GRPC_DEMO_UTILTY_H
