#ifndef Compiler_hpp
    #define Compiler_hpp

//{==============================================================================

#include "..//Librarys//Stream.hpp"
#include "..//Librarys//AbstractSyntaxNode.hpp"
//#include "Headers//Preprocessor.hpp"
#include "FrontEnd//SyntaxAnalyzer.hpp"
#include "FrontEnd//SemanticAnalyzer.hpp"

//}==============================================================================

//{==============================================================================

class Compiler
{
    public:
        Compiler  (AstNode& root, Stream <Token>& code, LogHTML& log);
};

//}==============================================================================

Compiler :: Compiler (AstNode& root, Stream <Token>& code, LogHTML& log)
    {
        //Preprocessor          preprocessor (code, log);
        SyntaxAnalyzer     syntax_analyzer (root, code, log);
        SemanticAnalyzer semantic_analyzer (root, log);
    }

#endif
