//
// Created by orit on 17/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include "Server.h"
#include "Defines.h"

class OpenServerCommand: public Command {
    Server* server = new Server();
public:
    int execute(list<string>::iterator it);
    void callingForAccept(int port);

    virtual ~OpenServerCommand();
};


#endif //EX3_OPENSERVERCOMMAND_H
