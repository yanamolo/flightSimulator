//
// Created by yana on 18/12/2019.
//

#include "Var.h"

Var::~Var() {
}

/** create var without sim */
Var::Var(string varName, float valueVar) {
    this->name = varName;
    this->direction.clear();
    this->sim.clear();
    this->value = valueVar;
}

/** create var without value */
Var::Var(string nameVar, string dirVar, string simVar) {
    this->name = nameVar;
    this->direction = dirVar;
    this->sim = simVar;
    this->value = NULL;
}

void Var::setValue(float valueVar) {
    this->value = valueVar;
}

Var::Var(const Var &var) {
    this->name = var.name;
    this->value = var.value;
    this->sim = var.sim;
    this->direction = var.direction;
}

string Var::getDirection() {
    return this->direction;
}

float Var::getValue() {
    return this->value;
}

string Var::getSim() {
    return this->sim;
}

string Var::getName() {
    return this->name;
}

