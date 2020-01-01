#include "Lexer.h"
#include "Parse.h"

int main() {
    try {
        Lexer *lex = new Lexer();
        list<string> flyList = lex->lexer();
        Parse *parseList = new Parse(flyList);
        parseList->parse();
    } catch (exception e) {
        cout << e.what() << endl;
    }


    return 0;
}