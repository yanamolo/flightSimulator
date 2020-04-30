//
// Created by orit on 19/12/2019.
//

#include "IfCommand.h"
#include "Parse.h"

int IfCommand::execute(list<string>::iterator it) {
    list<string>::iterator first_it = it;
    bool condition = conditionRes(it);
    advance(it, 5); // it is first command
    int jumps = createList(it);
    if (condition) {
        Parse *parser = new Parse(list_commands);
        parser->parse();
    }
    list_commands.clear();
    return jumps + 1;
}


int IfCommand::createList(list<string>::iterator it) {
    int jumps = 4;
    while (*it != "}") {
        list_commands.push_back(*it);
        it++;
        jumps++;
    }
    it++;
    return jumps + 1;
}


bool IfCommand::conditionRes(list<string>::iterator it) {
    Interpreter* inter = new Interpreter();
    it++; // it is the left expression
    this->val_left = inter->interpret(*it);
    it++; // it is the symbol (=, != ..)
    this->op = *it;
    it++; // it is the right expression
    this->val_right = inter->interpret(*it);
    delete inter;
    if (op == "<") {
        if (val_left < val_right) {
            return true;
        }
    } else if (op == ">") {
        if (val_left > val_right) {
            return true;
        }
    } else if (op == ">=") {
        if (val_left >= val_right) {
            return true;
        }
    } else if (op == "<=") {
        if (val_left <= val_right) {
            return true;
        }
    } else if (op == "==") {
        if (val_left == val_right) {
            return true;
        }
    } else if (op == "!=") {
        if (val_left != val_right) {
            return true;
        }
    }
    return false;
}