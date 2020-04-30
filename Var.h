//
// Created by yana on 18/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H
#include <string>
using namespace std;

class Var {
private:
    string name;
    string direction;
    string sim;
    float value;
public:
    ~Var();
    Var(string nameVar, string dirVar, string simVar);
    Var(string varName, float valueVar);
    void setValue(float valueVar);
    Var(const Var &var);
    string getDirection();
    float getValue();
    string getSim();
    string getName();
};


#endif //EX3_VAR_H
