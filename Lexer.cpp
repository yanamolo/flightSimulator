//
// Created by orit and Yana on 16/12/2019 which is Orit's birthday.
//

#include <fstream>
#include "Lexer.h"

using namespace std;

string Lexer::eraseSpaces(string toCheck) {
    string toReturn = "";
    int i;
    for (i = 0; i < toCheck.size(); i++) {
        if (toCheck[i] != ' ') {
            toReturn += toCheck[i];
        }
    }
    return toReturn;
}

Lexer::Lexer() {
    this->orders = list<string>();
}

list<string> Lexer::lexer(char* file_path) {
    ifstream inFile;
    inFile.open(file_path, ios::in);
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

string Lexer::eraseTabs(string line) {
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t') {
        i++;
    }
    if (i > 0) {
        line.erase(0, i);
    }
    return line;
}

void Lexer::splitLine(string line) {
    string temp;
    string name;

    /** check tab in the first 4 chars of the line */
    line = eraseTabs(line);

    /** check line by the command it starts with */
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
        line.erase(0, 3);
        if (line.find("->") != string::npos) {
            name = subTheString(line,0, line.find("->"));
            name = eraseSpaces(name);
            orders.push_back(name);
            orders.push_back("->");
            orders.push_back("sim");
            string location = subTheString(line, line.find("\""), line.find(")") - 1);
            orders.push_back(location);
        } else if (line.find("<-") != string::npos) {
            name = subTheString(line,0, line.find("<-"));
            name = eraseSpaces(name);
            orders.push_back(name);
            orders.push_back("<-");
            orders.push_back("sim");
            string location = subTheString(line, line.find("\""), line.find(")") - 1);
            orders.push_back(location);
        } else if (line.find("=") != string::npos){
            name = subTheString(line,0, line.find("="));
            name = eraseSpaces(name);
            orders.push_back(name);
            orders.push_back("=");
            string value = subTheString(line, line.find("="), line.size());
            value = eraseSpaces(value);
            orders.push_back(value);
        }
    } else if (line.find("if") != string::npos || line.find("while") != string::npos) {
        string parse;
        temp = subTheString(line, 0, line.find(" "));
        orders.push_back(temp);
        line.erase(0, temp.size() + 1);
        if (line.find("<=") != string::npos) {
            parse = "<=";
        } else if (line.find(">=") != string::npos) {
            parse = ">=";
        } else if (line.find("==") != string::npos) {
            parse = "==";
        } else if (line.find("!=") != string::npos) {
            parse = "!=";
        } else if (line.find(">") != string::npos) {
            parse = ">";
        } else if (line.find("<") != string::npos) {
            parse = "<";
        }
        name = subTheString(line, 0, line.find(parse));
        name = eraseSpaces(name);
        orders.push_back(name);
        orders.push_back(parse);
        string value = subTheString(line,line.find(parse) + 1, line.find("{"));
        value = eraseSpaces(value);
        orders.push_back(value);
        orders.push_back("{");
    } else if (line.find("}") != string::npos) {
        orders.push_back("}");
    } else {
        /** rest of the cases have no command- when we want to update a var */
        string nameOfVar = subTheString(line, 0, line.find("="));
        nameOfVar = eraseSpaces(nameOfVar);
        orders.push_back(nameOfVar);
        orders.push_back("=");
        temp = subTheString(line, line.find("="), line.size());
        temp = eraseSpaces(temp);
        orders.push_back(temp);
    }
}

/** substring by index */
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



