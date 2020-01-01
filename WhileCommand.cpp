//
// Created by orit on 19/12/2019.
//

#include "WhileCommand.h"
#include "Parse.h"

int WhileCommand::execute(list<string>::iterator it) {
    list<string>::iterator first_it = it;
    bool condition = conditionRes(it);
    advance(it, 5); // it is first command
    int jumps = createList(it);
    while (condition) {
        Parse *parser = new Parse(list_commands);
        parser->parse();
        condition = conditionRes(first_it);
    }
    return jumps;
}

int WhileCommand::createList(list<string>::iterator it) {
    int jumps = 4;
    while (*it != "}") {
        list_commands.push_back(*it);
        it++;
        jumps++;
    }
    return jumps;
}

bool WhileCommand::conditionRes(list<string>::iterator it) {
    Interpreter *inter = new Interpreter();
    it++; // it is the left expression
    Expression *ex_left = inter->interpret(*it);
    this->val_left = ex_left->calculate();
    it++; // it is the symbol (=, != ..)
    this->op = *it;
    it++; // it is the right expression
    Expression *ex_right = inter->interpret(*it);
    this->val_right = ex_right->calculate();
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