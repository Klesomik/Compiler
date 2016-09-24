#ifndef Compiler_hpp
    #define Compiler_hpp

//{==============================================================================

#include <ctime>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//AbstractSyntaxNode.hpp"
#include "FrontEnd//LexicialAnalyzer.hpp"
//#include "FrontEnd//Preprocessor.hpp"
#include "FrontEnd//SyntaxAnalyzer.hpp"
#include "FrontEnd//SemanticAnalyzer.hpp"
#include "FrontEnd//Optimizer.hpp"
#include "FrontEnd//CodeGeneration.hpp"

//}==============================================================================

//{==============================================================================

class Compiler
{
    private:
        Stream <Token> code;

        AstNode root;

    public:
        Compiler  (FILE* c_file, LogHTML& log, FILE* asm_file);
};

//}==============================================================================

Compiler :: Compiler (FILE* c_file, LogHTML& log, FILE* asm_file):
    code (),
    root ({ Block })
    {
        /*FILE* ast = fopen ("AST.txt", "r");

        assert (ast);

        root.read (ast);

        RenderTree (root, "..//Materials//Hello.dot", "..//Materials//ASTNew.jpg");*/

        log.setFontColor ("white");
        log.setSize      (100);
        log.setColor     ("blue");

        log.output ("========== Build started: DeerC %d.%d ==========\n", 1, 0);

        log.setColor ("red");
        clock_t start = clock ();

        LexicialAnalyzer lexicial_analyzer (c_file, code);
        //Preprocessor          preprocessor (code, log);
        SyntaxAnalyzer     syntax_analyzer (root, code, log);
        //SemanticAnalyzer semantic_analyzer (root, log);
        //Optimizer                optimizer (root);
        CodeGeneration     code_generation (root, asm_file, 1);

        clock_t end = clock ();
        log.setColor ("blue");

        RenderTree (root, "..//Materials//Hello.dot", "..//Materials//AST.jpg");

        log.output ("Build started on: %f\n",   (float) start / CLOCKS_PER_SEC);
        log.output ("Build   ended on: %f\n\n", (float)   end / CLOCKS_PER_SEC);

        log.output ("========== Build finished ==========\n");

        log.out ();

        FILE* ast = fopen ("..//Materials//AST.txt", "w");

        assert (ast);

        root.write (ast);

        fclose (ast);
    }

#endif
