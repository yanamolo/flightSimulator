//
// Created by orit on 18/12/2019.
//

#include "Interpreter.h"

using namespace std;

// get the full string number of variable
string Interpreter::getFullNumber(string s) {
    string number = "";
    for (unsigned int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]) || s[i] == '.') {
            number += s[i];
        } else {
            break;
        }
    }
    return number;
}

// when seeing ) sign, take out all signs in the stack until ( sign and move to the queue
void Interpreter::outCharsOfStack() {
    while (stackStr.top() != "(") {
        queuePostfix.push(stackStr.top());
        stackStr.pop();
    }
    stackStr.pop(); // take out the "("
    if (!stackStr.empty()) {
        if (stackStr.top() == "@") {
            queuePostfix.push(stackStr.top());
            stackStr.pop();
        }
    }
}

queue<string> Interpreter::infixToPostfix(string s) {

    if (s[0] == '-') {
        stackStr.push ("@");
        s = s.substr(1);
    }

    string copyString = s;
    int countParenthesis = 0;
    int digitLength = 0;
    bool bracketClosedNow = false;
    bool NumberNow = false;

    while (!copyString.empty()) {
        bool plusAfterClosing = false;
        if ((copyString[0] == '-') && (copyString[1] == '(')) {
            if (bracketClosedNow) {
                stackStr.push("-");
            } else if (NumberNow) {
                stackStr.push("+");
                stackStr.push("@");
            } else {
                stackStr.push("@");
            }
            stackStr.push("(");
            copyString = copyString.substr(2);
            countParenthesis++;
            bracketClosedNow = false;
            NumberNow = false;
            continue;

        } else if ((copyString[0] == '-') && (isdigit(copyString[1]))) {
            bracketClosedNow = false;
            NumberNow = true;
            if (copyString.length() != s.length()) {
                if (!stackStr.empty()) {
                    if (!(stackStr.top() == "(") && (!(stackStr.top() == "-"))) {
                        stackStr.push("+");
                    }
                } else if (!queuePostfix.empty()) {
                    stackStr.push("+");
                }
            }
            queuePostfix.push("0");
            string subStr = copyString.substr(1);
            string number = getFullNumber(subStr);
            queuePostfix.push(number);
            queuePostfix.push("-");

            copyString = copyString.substr(1 + number.length());
            continue;

        } else if (copyString[0] == '(') {
            bracketClosedNow = false;
            NumberNow = false;
            countParenthesis++;
            stackStr.push("(");
        } else if (copyString[0] == ')') {
            bracketClosedNow = true;
            NumberNow = false;
            if (countParenthesis == 0) {
                throw "Error! no '(' sign";
            }
            outCharsOfStack();
            countParenthesis--;
            if (copyString.length()!= 1) {
                if (copyString[1] == '+') {
                    while (!stackStr.empty()) {
                        if ((stackStr.top() == "*") || (stackStr.top() == "/")) {
                            queuePostfix.push(stackStr.top());
                            stackStr.pop();
                        } else {
                            break;
                        }
                    }
                    stackStr.push("+");
                    plusAfterClosing = true;
                }
            }
        } else if ((copyString[0] == '+') || (copyString[0] == '-')) {
            bracketClosedNow = false;
            NumberNow = false;
            while (!stackStr.empty()) {
                if ((stackStr.top() == "*") || (stackStr.top() == "/")) {
                    queuePostfix.push(stackStr.top());
                    stackStr.pop();
                } else {
                    break;
                }
            }
            if (copyString[0] == '+') {
                stackStr.push("+");
            } else {
                stackStr.push("-");
            }

        } else if (copyString[0] == '*') {
            bracketClosedNow = false;
            NumberNow = false;
            stackStr.push("*");
        } else if (copyString[0] == '/') {
            bracketClosedNow = false;
            NumberNow = false;
            stackStr.push("/");
        } else if (isdigit(copyString[0])) {
            bracketClosedNow = false;
            NumberNow = true;
            string number = getFullNumber(copyString);
            queuePostfix.push(number);
            digitLength = number.length();
            if (!stackStr.empty()) {
                if (stackStr.top() == "@") {
                    queuePostfix.push(stackStr.top());
                    stackStr.pop();
                }
            }
        }


        if (digitLength != 0) { // if digit read now
            copyString = copyString.substr(queuePostfix.back().length());
            if (copyString.length() >= 1) {
                if ((copyString[0] == '+') || (copyString[0] == '-')) {
                    while (!stackStr.empty()) {
                        if ((stackStr.top() == "*") || (stackStr.top() == "/")) {
                            queuePostfix.push(stackStr.top());
                            stackStr.pop();
                        } else {
                            break;
                        }
                    }
                    if (copyString[0] == '+') {
                        stackStr.push("+");
                    } else {
                        stackStr.push("-");
                    }
                    plusAfterClosing = true;
                    copyString = copyString.substr(1);
                }
            }
            digitLength = 0;
        } else if (plusAfterClosing) {
            copyString = copyString.substr(2);
            plusAfterClosing = false;
        } else {
            copyString = copyString.substr(1);
        }

    }

    if (countParenthesis != 0) {
        throw "no closing sign ')' ";
    }

    while (!stackStr.empty()) {
        queuePostfix.push(stackStr.top());
        stackStr.pop();
    }

    return queuePostfix;
}

Interpreter::Interpreter() {

}

// placing value of variable in the input string
string Interpreter::getExAfterPlacing(string str, string key, int startKey) {
    SymbolTable* symbolTable = symbolTable->getTable();

    map<string, Var*>::iterator it = symbolTable->getNameMap().find(key);
    while (it != symbolTable->getNameMap().end()) {
        string tmp = str.substr(0, startKey);
        string stringVal = to_string(it->second->getValue());
        if (stringVal[0] == '-') {
            string putBrackets = "(" + stringVal + ")";
            stringVal = putBrackets;
        }
        tmp += stringVal;
        str = tmp;
        break;
    }
    return str;
}

float Interpreter::interpret(string s) {

    setVariables(&s);

    // if the string is in 1 length
    if (s.length() == 1) {
        if (isdigit(s[0])) {
            Expression* e = new Value (stof(s));
            return  e->calculate();
            //return e;
        } else {
            throw "invalid string";
        }
    }

    //check validation- when there are tew signs in a row the string is not valid!
    int counter = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        if ((s[i] == '*') || (s[i] == '/') || (s[i] == '-') ||(s[i] == '+')) {
            counter++;
            if (counter == 2) {
                throw "invalid string";
            }
        } else if ((i > 0) && (s[i] == '(') && (s[i-1] ==')')) {
            throw "invalid string - )( without binary/unary sign";
        } else {
            counter = 0;
        }
    }

    queue<string> postFix = infixToPostfix(s);

    //create the expression while using the stack of expressions
    stack<Expression*> expressions;
    while (!queuePostfix.empty()) {
        if (queuePostfix.front() == "@") {
            Expression *x = expressions.top();
            expressions.pop();
            expressions.push(new UMinus(x));
        } else if ((queuePostfix.front() != "*") && (queuePostfix.front() != "/") &&
                   (queuePostfix.front() != "+") && (queuePostfix.front() != "-")) {
            float number = stof(queuePostfix.front());
            Value *val = (new Value(number));
            expressions.push(val);
        } else {
            Expression *y = expressions.top();
            expressions.pop();
            if (expressions.empty()) {
                if (queuePostfix.front() == "+") {
                    expressions.push(new UPlus(y));
                    queuePostfix.pop();
                    continue;
                } else {
                    throw "not enough expressions for binary action";
                }
            }
            Expression *x = expressions.top();
            expressions.pop();
            if (queuePostfix.front() == "*") {
                expressions.push(new Mul(x, y));
            } else if (queuePostfix.front() == "/") {
                expressions.push(new Div(x, y));
            } else if (queuePostfix.front() == "+") {
                expressions.push(new Plus(x, y));
            } else if (queuePostfix.front() == "-") {
                expressions.push(new Minus(x, y));
            }
        }
        queuePostfix.pop();
    }

    float value = expressions.top()->calculate();
    delete expressions.top();
    return value;
}

/**
 * setVariables - insert map all keys ans values of varibles in the string
 * @param vars string of variables
 */
void Interpreter::setVariables(string *s) {
    SymbolTable* symbolTable = symbolTable->getTable();
    string str = *s;
    bool partOfKey = false;
    string key = "";
    int startKey;

    //placing values of vars from symbolTable
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            continue;
        }

        if ((str[i] == ('/')) || (str[i] == ('-')) || (str[i] == ('+')) || (str[i] == ('*')) ||
            (str[i] == ('(')) || (str[i] == (')'))) {
            if (!partOfKey) {
                continue;
            }
            partOfKey = false; // end of key
            auto it = symbolTable->getNameMap().find(key);
            Var *var = it->second;

            string tmp;
            string stringVal;
            try {
                float num = stof(key);
                tmp = str.substr(0, startKey);
                stringVal = key;
                tmp += stringVal;
                key = "";
                continue;
            } catch (exception &e) {
                tmp = str.substr(0, startKey);
                stringVal = to_string(it->second->getValue());

                if (stringVal[0] == '-') {
                    string putBrackets = "(" + stringVal + ")";
                    stringVal = putBrackets;
                }
                tmp += stringVal;
                int j = i;
                i = tmp.length() /*- 1*/;
                tmp += str.substr(j);
                str = tmp;
                key = "";
            }
        } else { // part of key
            if (!partOfKey) { // save the start of Key index
                partOfKey = true;
                startKey = i;
            }
            key += str[i];
            if (str.length() - 1 == i) {
                str = getExAfterPlacing(str, key, startKey);
                i = str.length();
            }
        }
    }

    if (partOfKey) { // if the end of string was a var
        string tmp;
        string stringVal;
        try {
            float num = stof(key);
            tmp = str.substr(0, startKey);
            stringVal = key;
        } catch (exception &e) {

            auto it = symbolTable->getNameMap().find(key);
            Var *var = it->second;

            if (var != nullptr) { // if found in symbolTable
                tmp = str.substr(0, startKey);
                stringVal = to_string(it->second->getValue());

                if (stringVal[0] == '-') {
                    string putBrackets = "(" + stringVal + ")";
                    stringVal = putBrackets;
                }

            }
        }
        tmp += stringVal;
        str = tmp;
    }
    //update the real string s
    *s = str;
}

Variable::Variable(string n, float v) : name(n), value(v) {}

Variable &Variable::operator+=(float x) {
    value += x;
    return *this;
}

Variable &Variable::operator-=(float x) {
    value -= x;
    return *this;
}

Variable &Variable::operator--() {
    value--;
    return *this;
}

Variable &Variable::operator++() {
    value++;
    return *this;
}

Variable &Variable::operator--(int) {
    value--;
    return *this;
}

Variable &Variable::operator++(int) {
    value++;
    return *this;
}

float Variable::calculate() { return this->value; }

Value::Value(float d) : val(d) {}
float Value::calculate() { return this->val; }

UPlus::UPlus(Expression *ex) {
    e = ex;
}
UPlus::~UPlus() {
    delete e;
}
float UPlus::calculate() {
    return e->calculate();
}


UMinus::UMinus(Expression *ex) {
    e = ex;
}
UMinus::~UMinus() {
    delete e;
}
float UMinus::calculate() {
    return -1 * (e->calculate());
}

Plus::Plus(Expression *ex1, Expression *ex2) {
    left = ex1;
    right = ex2;
}
Plus::~Plus() {
    delete left;
    delete right;
}
float Plus::calculate() {
    return left->calculate() + right->calculate();
}

Minus::Minus(Expression *ex1, Expression *ex2) {
    left = ex1;
    right = ex2;
}
Minus::~Minus() {
    delete left;
    delete right;
}
float Minus::calculate() {
    return left->calculate() - right->calculate();
}

Mul::Mul(Expression *ex1, Expression *ex2) {
    left = ex1;
    right = ex2;
}
Mul::~Mul() {
    delete left;
    delete right;
}
float Mul::calculate() {
    return left->calculate() * right->calculate();
}

Div::Div(Expression *ex1, Expression *ex2) {
    left = ex1;
    right = ex2;
}
Div::~Div() {
    delete left;
    delete right;
}
float Div::calculate() {
    float resRight = right->calculate();
    if (resRight == 0) {
        throw "can't divide in 0";
    }
    return left->calculate() / resRight;
}
