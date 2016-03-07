//#include "Stream.hpp"
//#include "AbstractSyntaxTree.hpp"
//#include "Preprocessor.hpp"
#include "SyntaxAnalyzer.hpp"
#include "SemanticAnalyzer.hpp"

class Compiler
{
    public:
        Compiler (AstNode& root, Stream <Token>& code);
};

Compiler :: Compiler (AstNode& root, Stream <Token>& code)
{
    //Preprocessor          preprocessor (code);
    SyntaxAnalyzer     syntax_analyzer (root, code);
    SemanticAnalyzer semantic_analyzer (root);
}
