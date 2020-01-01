//
// Created by yana on 18/12/2019.
//

#ifndef EX3_SYMBOLTABLE_H
#define EX3_SYMBOLTABLE_H

#include <map>
#include <string>
#include <iostream>
#include "Var.h"
#include <list>
#include <queue>
#include <mutex>

using namespace std;

class SymbolTable {
private:
    bool run = true;
    static SymbolTable *tableObj;
    map<string, Var *> mapBySim;
    map<string, Var *> mapByName;
    queue<string> info_to_send;
    list <string> sims_for_server;
    mutex nameLock, simLock;

    SymbolTable() = default;

    void addVarBySim(const string &sim, Var *var);

    void addVarByName(const string &name, Var *var);

    void setVarDataByName(const string &name, float value);

public:
    ~SymbolTable();

    void setVarDataBySim(const string &sim, float value);

    static SymbolTable *getTable();

    map<string, Var *> getNameMap();

    map<string, Var *> getSimMap();

    Var *getVarBySim(const string &sim);

    Var *getVarByName(const string &name);

    void lockExecute(char flag, const string &sim, const string &name, string direcion, float value);

    bool getIfRun();

    void changeBool();

    queue<string> getMessages();

    list <string> getSimsForServer();

    void pop_from_Messages();
};


#endif //EX3_SYMBOLTABLE_H
