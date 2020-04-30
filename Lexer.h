//
// Created by orit and Yana on 16/12/2019 which is Orit's birthday.
//

#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include "Defines.h"

class Lexer {
private:
    list<string> orders;
public:
    string eraseTabs(string line);
    string eraseSpaces(string toCheck);
    Lexer();
    string subTheString(string sub, int start, int end);
    list<string> lexer(char* file_path);
    void splitLine(string line);
};


#endif //EX3_LEXER_H
