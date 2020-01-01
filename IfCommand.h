//
// Created by orit on 19/12/2019.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H

#include "Command.h"


class IfCommand : public Command {
public:
    int execute(list<string>::iterator it);
};


#endif //EX3_IFCOMMAND_H
