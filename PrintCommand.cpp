//
// Created by orit on 17/12/2019.
//

#include "PrintCommand.h"

int PrintCommand::execute(list<string>::iterator it) {
    it++;
    string to_print = *it;
    if ((to_print[0] != '"') && (to_print[to_print.size() - 1] != '"')) {
        Interpreter *inter = new Interpreter();
        Expression *ex = inter->interpret(to_print);
        float val_print = ex->calculate();
        to_print = to_string(val_print);
    }
    cout << to_print << endl;

    if (*it == "done") {
        SymbolTable *s = s->getTable();
        s->changeBool();
        // finish program
    }
    return 2;
}