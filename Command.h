//
// Created by orit on 17/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H
#include "Defines.h"

class Command {
public:
    virtual int execute(list<string>::iterator it) = 0;
};

#endif //EX3_COMMAND_H
