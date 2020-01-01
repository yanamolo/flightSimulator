//
// Created by yana on 18/12/2019.
//


#include <utility>
#include "SymbolTable.h"

SymbolTable *SymbolTable::tableObj = 0;

SymbolTable::~SymbolTable() {
    map<string, Var *>::iterator it;
    for (it = this->getNameMap().begin(); it != this->getNameMap().end(); it++) {
        delete it->second;
    }
    for (it = this->getSimMap().begin(); it != this->getSimMap().end(); it++) {
        delete it->second;
    }
    delete this->tableObj;
}

class SymbolTable *SymbolTable::getTable() {
    if (!tableObj) {
        tableObj = new SymbolTable;
    }
    return tableObj;
}

map<string, class Var *> SymbolTable::getNameMap() {
    return this->mapByName;
}

map<string, class Var *> SymbolTable::getSimMap() {
    return this->mapBySim;
}

class Var *SymbolTable::getVarBySim(const string &sim) {
    map<string, Var *>::iterator it;
    for (it = this->mapBySim.begin(); it != this->mapBySim.end(); it++) {
        if (it->first.compare(sim) == 0) {
            Var *var = it->second;
            return var;
        }
    }
    return nullptr;
}

class Var *SymbolTable::getVarByName(const string &name) {
    map<string, Var *>::iterator it;
    for (it = this->mapByName.begin(); it != this->mapByName.end(); it++) {
        if (it->first == name) {
            Var *var = it->second;
            return var;
        }
    }
    return nullptr;
}

void SymbolTable::setVarDataBySim(const string &sim, float value) {
    this->simLock.lock();
    auto it = mapBySim.find(sim);
    if (it != mapBySim.end()) {
        it->second->setValue(value);
        auto it_name = this->mapByName.find(it->second->getName());
        it_name->second->setValue(value);
    }
    this->simLock.unlock();
}

void SymbolTable::setVarDataByName(const string &name, float value) {
    this->nameLock.lock();
    auto it = mapByName.find(name);
    if (it != mapByName.end()) {
        it->second->setValue(value);
        auto it_sim = this->mapBySim.find(it->second->getSim());
        it_sim->second->setValue(value);
    }
    if (mapByName.find(name)->second->getDirection() == "->") {
        string message = "set" + mapByName.find(name)->second->getSim() + " " + to_string(value) + "\r\n";
        info_to_send.push(message);
    }
    this->nameLock.unlock();
}

void SymbolTable::addVarBySim(const string &sim, class Var *var) {
    this->simLock.lock();
    this->mapBySim.insert(pair<string, Var *>(sim, var));
    if (var->getDirection() == "<-") {
        sims_for_server.push_back(sim);
    }
    this->simLock.unlock();
}

void SymbolTable::addVarByName(const string &name, Var *var) {
    this->nameLock.lock();
    this->mapByName.insert(pair<string, Var *>(name, var));
    this->nameLock.unlock();
}

void SymbolTable::lockExecute(char flag, const string &sim, const string &name, string direction, float value) {
    //mutex mutex_lock;
    //mutex_lock.lock();
    if (flag == 's') {
        if (sim.empty()) {
            setVarDataByName(name, value);
        } else if (name.empty()) {
            setVarDataBySim(sim, value);
        }
    }
    if (flag == 'a') {
        if (sim.empty()) {
            Var *var = new Var(name, value);
            this->addVarByName(var->getName(), var);
        } else {
            Var *var = new Var(name, direction, sim);
            this->addVarBySim(var->getSim(), var);
            this->addVarByName(var->getName(), var);
        }

    }
    //mutex_lock.unlock();
}

void SymbolTable::changeBool() {
    this->run = false;
}

bool SymbolTable::getIfRun() {
    return this->run;
}

queue<string> SymbolTable::getMessages() {
    if (!info_to_send.size()) {

    }
    return this->info_to_send;
}

list<string> SymbolTable::getSimsForServer() {
    return this->sims_for_server;
}

void SymbolTable::pop_from_Messages() {
    this->info_to_send.pop();
}
