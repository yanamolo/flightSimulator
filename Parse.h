//
// Created by orit on 17/12/2019.
//

#ifndef EX3_PARSE_H
#define EX3_PARSE_H
#include "Defines.h"
#include "Command.h"

class Parse {
private:
    map<string, Command*> commandMap;
    list<string> flyCommand;
public:
    Parse(list<string> flyList);
    void createMap();
    void parse();

    ~Parse();
};


#endif //EX3_PARSE_H
