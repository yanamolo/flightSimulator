//
// Created by yana on 19/12/2019.
//

#include "ConnectCommand.h"
 void ConnectCommand::callingForSending(int port, const char* ip) {
    this->client->creatConnection(port, ip);
}

int ConnectCommand::execute(list<string>::iterator it) {
    SymbolTable* s = s->getTable();
    it++;
    const char* ip = (*it).c_str();
    it++;
    int port;
    try {
        port = stoi(*it);
    } catch (exception& e) {
        auto* inter = new Interpreter();
        port = (int) inter->interpret(*it);
        delete inter;
    }
    auto* t2 = new thread(&ConnectCommand::callingForSending, this, port, ip);
    s->update_threads(t2);
    t2->detach();
    return 3;
}