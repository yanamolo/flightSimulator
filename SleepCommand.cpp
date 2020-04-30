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
    } catch (exception& e) {
        Interpreter* inter = new Interpreter();
        float value = inter->interpret(*it);
        miliseconds = (int) value;
        delete inter;
    }
    this_thread::sleep_for(chrono::milliseconds(miliseconds));
    return 2;
}