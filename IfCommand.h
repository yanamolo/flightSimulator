//
// Created by orit on 19/12/2019.
//

#ifndef EX3_IFCOMMAND_H
#define EX3_IFCOMMAND_H
#include "Command.h"


class IfCommand : public Command {
    float val_left;
    float val_right;
    string op;
    list<string> list_commands;
public:
    int execute(list<string>::iterator it);
    bool conditionRes(list<string>::iterator it);
    int createList(list<string>::iterator it);

};


#endif //EX3_IFCOMMAND_H
