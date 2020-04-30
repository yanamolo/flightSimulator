//
// Created by orit on 17/12/2019.
//

#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H

#include "Command.h"
#include "Defines.h"

class SleepCommand: public Command {
public:
    int execute(list<string>::iterator it);
};



#endif //EX3_SLEEPCOMMAND_H
