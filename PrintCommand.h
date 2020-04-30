//
// Created by orit on 17/12/2019.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "Command.h"
#include "Defines.h"

class PrintCommand: public Command {
public:
    int execute(list<string>::iterator it);
};

#endif //EX3_PRINTCOMMAND_H
