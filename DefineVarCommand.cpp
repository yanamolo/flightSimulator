//
// Created by orit on 17/12/2019.
//

#include "DefineVarCommand.h"
#include "Interpreter.h"

int DefineVarCommand::execute(list<string>::iterator it) {
    SymbolTable *s = s->getTable();
    Interpreter *inter = new Interpreter();
    string varName = "";
    if (*it == "var") {
        it++;
        varName = *it;
        it++;
        string arrow = *it;
        it++;
        if (*it == "sim") {
            it++;
            s->lockExecute('a', *it, varName, arrow, MAXVAL);
            return 5;
        } else {
            Expression *ex = inter->interpret(*it);
            float value = ex->calculate();
            s->lockExecute('a', "", varName, arrow, value);
            return 4;
        }
    } else {
        varName = *it;
        it++; // it points to =
        it++; // it points to the value expression
        Expression *ex = inter->interpret(*it);
        float value = ex->calculate();
        s->lockExecute('s', "", varName, "=", value);
        return 3;
    }
}
