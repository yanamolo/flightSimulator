//
// Created by orit on 17/12/2019.
//

#include "PrintCommand.h"

int PrintCommand::execute(list<string>::iterator it) {
    it++;
    string to_print = *it;

    /** find if we need to print a message or expression that we need to interpret before printing */
    if ((to_print[0] != '"') && (to_print[to_print.size()-1] != '"')) {
        Interpreter* inter = new Interpreter();
        float val_print = inter->interpret(*it);
        to_print = to_string(val_print);
        delete inter;
    } else {
        to_print = to_print.substr(1, to_print.size() - 2);
    }
    cout << to_print << endl;
    if (to_print == "done" || to_print == "Done") {
        SymbolTable *s = s->getTable();
        s->changeBool();
        // finish program
    }
    return 2;
}