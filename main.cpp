#include "Lexer.h"
#include "Parse.h"

int main(int argc, char *argv[]) {
    try {
        Lexer* lex = new Lexer();
        char* file_path = argv[1];
        list<string> flyList = lex->lexer(file_path);
        Parse* parser = new Parse(flyList);
        parser->parse();
        delete lex;
    } catch (exception e) {
        cout << e.what() << endl;
    }




    return 0;
}