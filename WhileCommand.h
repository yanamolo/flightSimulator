//
// Created by orit on 19/12/2019.
//

#ifndef EX3_WHILECOMMAND_H
#define EX3_WHILECOMMAND_H
#include "Command.h"

class WhileCommand : public Command {
    float val_left;
    float val_right;
    string op;
    list<string> list_commands;
public:
    int execute(list<string>::iterator it);
    bool conditionRes(list<string>::iterator it);
    int createList(list<string>::iterator it);
};


#endif //EX3_WHILECOMMAND_H
