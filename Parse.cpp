//
// Created by orit on 17/12/2019.
//

#include "Parse.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"

Parse::Parse(list<string> fly) {
    this->flyCommand = fly;
    this->createMap();
}

/** create command map for finding the command we want to execute by the command's name */
void Parse::createMap() {
    commandMap.insert({"openDataServer",new OpenServerCommand()});
    commandMap.insert({"connectControlClient",new ConnectCommand()});
    commandMap.insert({"var",new DefineVarCommand()});
    commandMap.insert({"Print",new PrintCommand()});
    commandMap.insert({"Sleep",new SleepCommand()});
    commandMap.insert({"while",new WhileCommand()});
    commandMap.insert({"if",new IfCommand()});
}

/** execute all commands in the list flyCommand and finish program after it's done */
void Parse::parse() {
    int index = 0;
    SymbolTable* s = s->getTable();
    while (index < flyCommand.size()) {
        auto it = this->flyCommand.begin();
        advance(it, index);
        map<string, Command*>::iterator iterator = commandMap.find(*it);

        if (iterator != commandMap.end()) {
            Command* c = commandMap.find(*it)->second;
            index += c->execute(it);
        } else {
            DefineVarCommand *defineVarCommand = new DefineVarCommand();
            index += defineVarCommand->execute(it);
            delete defineVarCommand;
        }
        if (!s->getIfRun()) {
            break;
        }
    }

}

Parse::~Parse() {
    map<string, Command *>::iterator it;
    for (it = this->commandMap.begin(); it != this->commandMap.end(); it++) {
        delete it->second;
    }
}