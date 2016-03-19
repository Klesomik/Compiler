#ifndef Compiler_hpp
    #define Compiler_hpp

//{==============================================================================

#include "Stream.hpp"
#include "AbstractSyntaxNode.hpp"
//#include "Preprocessor.hpp"
#include "SyntaxAnalyzer.hpp"
#include "SemanticAnalyzer.hpp"

//}==============================================================================

//{==============================================================================

class Compiler
{
    private:
        LogHTML log_;

    public:
        Compiler  (AstNode& root, Stream <Token>& code);
        ~Compiler ();

        void Hello_Log (std::string& example);
};

//}==============================================================================

Compiler :: Compiler (AstNode& root, Stream <Token>& code):
    log_ ()
    {
        std::string name;
        Hello_Log (name);

        log_.open (name.c_str ());

        log_.setFontColor ("black");
        log_.setSize      (100);
        log_.setColor     ("yellow");

        log_.output ("===== Build started =====\n");

        Preprocessor          preprocessor (code, log_);
        SyntaxAnalyzer     syntax_analyzer (root, code, log_);
        SemanticAnalyzer semantic_analyzer (root, log_);

        log.output ("===== Build finished =====\n");
    }

//===============================================================================

Compiler :: ~Compiler ()
{
    log_.close ();
}

//===============================================================================

void Compiler :: Hello_Log (std::string& example)
{
    printf ("Input name of Log file: ");

    getline (std::cin, example, '\n');
}

#endif
