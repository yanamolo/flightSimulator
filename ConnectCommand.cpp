//
// Created by yana on 19/12/2019.
//

#include "ConnectCommand.h"

void ConnectCommand::callingForSending(int port, const char *ip) {
    this->client->creatConnection(port, ip);
}

int ConnectCommand::execute(list<string>::iterator it) {
    it++;
    const char *ip = (*it).c_str();
    it++;
    int port;
    try {
        port = stoi(*it);
    } catch (exception &e) {
        auto *inter = new Interpreter();
        Expression *ex = inter->interpret(*it);
        port = (int) ex->calculate();
    }
    auto *t2 = new thread(&ConnectCommand::callingForSending, this, port, ip);
    //thread t2(&ConnectCommand::callingForSending, this, port, ip);
    t2->detach();
    return 3;
}