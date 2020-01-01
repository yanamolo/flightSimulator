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

void Parse::createMap() {
    commandMap.insert({"openDataServer", new OpenServerCommand()});
    commandMap.insert({"connectControlClient", new ConnectCommand()});
    commandMap.insert({"var", new DefineVarCommand()});
    commandMap.insert({"Print", new PrintCommand()});
    commandMap.insert({"Sleep", new SleepCommand()});
    commandMap.insert({"while", new WhileCommand()}); // create
    commandMap.insert({"if", new IfCommand()}); // create
}

void Parse::parse() {
    int index = 0;
    while (index < flyCommand.size()) {
        auto it = this->flyCommand.begin();
        advance(it, index);
        map<string, Command *>::iterator iterator = commandMap.find(*it);

        if (iterator != commandMap.end()) {
            Command *c = commandMap.find(*it)->second;
            index += c->execute(it);
        } else {
            DefineVarCommand *defineVarCommand = new DefineVarCommand();
            index += defineVarCommand->execute(it);
        }
    }

}