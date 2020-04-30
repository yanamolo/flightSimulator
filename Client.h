//
// Created by yana on 19/12/2019.
//

#ifndef EX3_CLIENT_H
#define EX3_CLIENT_H
#include <netinet/in.h>
#include "Defines.h"
using namespace std;

class Client {
public:
    void creatConnection(int port,const char* ip);
};


#endif //EX3_CLIENT_H
