//
// Created by orit on 17/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H
#include "Command.h"

class DefineVarCommand: public Command {
public:
    int execute(list<string>::iterator it);
};

#endif //EX3_DEFINEVARCOMMAND_H
