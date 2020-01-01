//
// Created by orit on 17/12/2019.
//

#include "SleepCommand.h"
#include "Interpreter.h"

int SleepCommand::execute(list<string>::iterator it) {
    it++;
    int miliseconds;
    try {
        miliseconds = stoi(*it);
    } catch (exception &e) {
        Interpreter *inter = new Interpreter();
        Expression *ex = inter->interpret(*it);
        float value = ex->calculate();
        miliseconds = (int) value;
    }
    miliseconds = miliseconds / 1000;
    this_thread::sleep_for(chrono::milliseconds(miliseconds));
    return 2;
}