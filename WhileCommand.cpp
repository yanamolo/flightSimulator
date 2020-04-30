//
// Created by orit on 19/12/2019.
//

#include "WhileCommand.h"
#include "Parse.h"

/** create list of all commands in the while scope and execute these commands with new parser
 *  in the end of the loop we check the condition for continue or end the loop */
int WhileCommand::execute(list<string>::iterator it) {
    list<string>::iterator first_it = it;
    bool condition = conditionRes(it);
    Parse *parser;
    advance(it, 5); // it is first command
    int jumps = createList(it);
    while (condition) {
        parser = new Parse(list_commands);
        parser->parse();
        condition = conditionRes(first_it);
    }
    list_commands.clear();
    return jumps + 1;
}

int WhileCommand::createList(list<string>::iterator it) {
    int jumps = 4;
    while (*it != "}") {
        list_commands.push_back(*it);
        it++;
        jumps++;
    }
    it++;
    return jumps + 1;
}

bool WhileCommand::conditionRes(list<string>::iterator it) {
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