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
        LogHTML& log_;

    public:
        Compiler  (AstNode& root, Stream <Token>& code);
        ~Compiler ();

        void init ();

        void Hello_Log (std::string& example);
};

//}==============================================================================

Compiler :: Compiler (AstNode& root, Stream <Token>& code):
    log_ ()
    { init (); }

//===============================================================================

Compiler :: ~Compiler ()
{
    log_.close ();
}

//===============================================================================

void Compiler :: init ()
{
    std::string name;
    Hello_Log (name);

    log_.open (name.c_str ());

    log.setFontColor ("black");
    log.setSize      (100);
    log.setColor     ("yellow");

    size_t error = 0;

    //Preprocessor preprocessor (code, log_);
        //error += preprocessor.error ();

    SyntaxAnalyzer syntax_analyzer (root, code, log_);
          error += syntax_analyzer.error ();

    SemanticAnalyzer semantic_analyzer (root, log_);
            error += semantic_analyzer.error ();

    log.output ("===== Build finished: %d errors =====\n", error);
}

//===============================================================================

void Compiler :: Hello_Log (std::string& example)
{
    printf ("Input name of Log file: ");

    getline (std::cin, example, '\n');
}
