//
// Created by orit on 18/12/2019.
//

#ifndef EX3_INTERPRETER_H
#define EX3_INTERPRETER_H
#include "Defines.h"
#include "SymbolTable.h"
#include <stack>
#include <queue>

class Expression {

public:
    virtual float calculate() = 0;
    virtual ~Expression() {}
};


class Interpreter {
    queue <string> queuePostfix;
    stack <string> stackStr;
public:
    Interpreter();
    float interpret(string s);
    void setVariables (string *s);
    void outCharsOfStack();
    string getFullNumber(string s);
    string getExAfterPlacing(string str, string key, int startKey);
    queue<string> infixToPostfix(string s);
};


class Variable: public Expression{
    string name;
    float value;
public:
    Variable(string n, float v);
    Variable& operator+=(float x);
    Variable& operator-=(float x);
    Variable& operator++();
    Variable& operator--();
    Variable& operator--(int);
    Variable& operator++(int);
    float calculate();
};

class Value: public Expression{
    float val;
public:
    Value(float f);
    float calculate();
};

class UnaryOperator: public Expression{
protected:Expression* e;
};

class BinaryOperator: public Expression{
protected:
    Expression* right;
    Expression* left;
};

class UMinus: public UnaryOperator{
public:
    UMinus(Expression* ex);
    ~UMinus();
    float calculate();
};

class UPlus: public UnaryOperator{
public:
    UPlus(Expression* ex);
    ~UPlus();
    float calculate();
};

class Plus: public BinaryOperator{
public:
    Plus(Expression* ex1, Expression* ex2);
    ~Plus();
    float calculate();
};

class Minus: public BinaryOperator{
public:
    Minus(Expression* ex1, Expression* ex2);
    ~Minus();
    float calculate();
};

class Mul: public BinaryOperator{
public:
    Mul(Expression* ex1, Expression* ex2);
    ~Mul();
    float calculate();
};

class Div: public BinaryOperator{
public:
    Div(Expression* ex1, Expression* ex2);
    ~Div();
    float calculate();
};

#endif //EX3_INTERPRETER_H
