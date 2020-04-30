//
// Created by yana on 19/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H

#include "Client.h"
#include "Command.h"
#include "Defines.h"

class ConnectCommand: public Command {
private:
    Client* client = new Client();
public:
    int execute(list<string>::iterator it);
    void callingForSending(int port,const char* ip);
};


#endif //EX3_CONNECTCOMMAND_H
