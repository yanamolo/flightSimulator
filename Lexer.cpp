//
// Created by orit and Yana on 16/12/2019 which is Orit's birthday.
//

#include <fstream>
#include "Lexer.h"

using namespace std;

string Lexer::eraseSpaces(string from, string to, string allString) {
    int indexFrom = allString.find(from) + from.size();
    int indexTo = allString.find(to);
    string res = "";
    for (int i = indexFrom; i < indexTo; i++) {
        if (allString[i] == ' ') {
            continue;
        } else {
            res += allString[i];
        }
    }

    return res;
}

Lexer::Lexer() {
    this->orders = list<string>();
}

list<string> Lexer::lexer() {
    ifstream inFile;
    inFile.open("fly.txt", ios::in);
    if (!inFile) {
        cerr << "ERROR! failed opening file" << endl;
        exit(1);
    }
    string line;
    while (getline(inFile, line)) {
        splitLine(line);
    }
    return orders;
}

void Lexer::splitLine(string line) {
    string temp;
    string name;

    if (line.find("\t") != string::npos) {
        line = line.substr(1);
    }

    if ((line.find("openDataServer") != string::npos) || (line.find("Sleep") != string::npos)
        || (line.find("Print") != string::npos)) {
        string nameOfOrder = subTheString(line, 0, line.find("("));
        orders.push_back(nameOfOrder);
        temp = subTheString(line, line.find("("), line.find(")"));
        orders.push_back(temp);
    } else if (line.find("connectControlClient") != string::npos) {
        orders.push_back("connectControlClient");
        string ip = subTheString(line, line.find("(") + 1, line.find(",") - 1);
        string socket = subTheString(line, line.find(","), line.find(")"));
        orders.push_back(ip);
        orders.push_back(socket);
    } else if (line.find("var") != string::npos) {
        orders.push_back("var");
        if (line.find("->") != string::npos) {
            name = eraseSpaces("var", "->", line);
            orders.push_back(name);
            orders.push_back("->");
            orders.push_back("sim");
            string location = subTheString(line, line.find("("), line.find(")"));
            orders.push_back(location);
        } else if (line.find("<-") != string::npos) {
            name = eraseSpaces("var", "<-", line);
            orders.push_back(name);
            orders.push_back("<-");
            orders.push_back("sim");
            string location = subTheString(line, line.find("("), line.find(")"));
            orders.push_back(location);
        } else if (line.find("=") != string::npos) {
            name = eraseSpaces("var", "=", line);
            orders.push_back(name);
            orders.push_back("=");
            string value = subTheString(line, line.find("="), line.size());
            orders.push_back(value);
        }
    } else if (line.find("if") != string::npos || line.find("while") != string::npos) {
        int parse;
        temp = subTheString(line, 0, line.find(" "));
        orders.push_back(temp);
        if (line.find("<=") != string::npos) {
            parse = line.find("<=");
            name = eraseSpaces(temp, "<=", line);
        } else if (line.find(">=") != string::npos) {
            parse = line.find(">=");
            name = eraseSpaces(temp, ">=", line);
        } else if (line.find("==") != string::npos) {
            parse = line.find("==");
            name = eraseSpaces(temp, "==", line);
        } else if (line.find("!=") != string::npos) {
            parse = line.find("!=");
            name = eraseSpaces(temp, "!=", line);
        } else if (line.find(">") != string::npos) {
            parse = line.find(">");
            name = eraseSpaces(temp, ">", line);
            parse--;
        } else if (line.find("<") != string::npos) {
            parse = line.find("<");
            name = eraseSpaces(temp, "<", line);
            parse--;
        }
        orders.push_back(name);
        orders.push_back(line.substr(parse, 2));
        string value = subTheString(line, parse + 2, line.size() - 2);
        orders.push_back(value);
        orders.push_back("{");
    } else if (line.find("}") != string::npos) {
        orders.push_back("}");
    } else {
        string nameOfVar = subTheString(line, 0, line.find(" "));
        orders.push_back(nameOfVar);
        orders.push_back("=");
        temp = subTheString(line, line.find("=") + 1, line.size());
        orders.push_back(temp);
    }
}

string Lexer::subTheString(string sub, int start, int end) {
    string s = "";
    bool flag = false;
    for (int i = 0; i < sub.size(); i++) {
        if (i == start) {
            flag = true;
            if (start == 0) {
                s += sub[i];
            }
            continue;
        } else if (i == end) {
            break;
        } else if (flag == true) {
            s += sub[i];
        }
    }
    return s;
}



