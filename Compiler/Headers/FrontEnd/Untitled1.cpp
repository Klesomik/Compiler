#include "LexicialAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"

void Hello_Log (std::string& example);

int main ()
{
    Stream <Token> code;

    LexicialAnalyzer lexicial_analyzer (code);

    code.dump ();

    std::string name;
    Hello_Log (name);

    LogHTML log;

    log.open (name.c_str ());

    log.setFontColor ("black");
    log.setSize      (100);
    log.setColor     ("yellow");

    log.output ("===== Build started =====\n");

    AstNode root;

    SyntaxAnalyzer   syntax_analyzer (root, code, log);

    log.output ("===== Build finished =====\n");

    return 0;
}

void Hello_Log (std::string& example)
{
    printf ("Input name of Log file: ");

    getline (std::cin, example, '\n');
}
