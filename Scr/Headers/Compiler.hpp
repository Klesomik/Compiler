#ifndef Compiler_hpp
    #define Compiler_hpp

//{==============================================================================

#include <cstdio>
#include <ctime>
#include <iostream>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//AbstractSyntaxNode.hpp"
#include "..//Libraries//LogHTML.hpp"
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

        FILE* file_source;
        FILE* file_asm;

        LogHTML file_log;

        Compiler (const Compiler& from);
        Compiler& operator = (const Compiler& from);

    public:
        Compiler (InputInformation& scan);

        ~Compiler ();

        void Start (InputInformation& scan);

        void Lexicial     (bool flag);
        void Preproc      (bool flag);
        void Syntax       (bool flag);
        void Semantic     (bool flag);
        void Optimize     (bool flag);
        void DisSyntax    (bool flag);
        void Generate     (bool flag);
        void DisGenerator (bool flag);

        void LogBegin ();
        void LogEnd (clock_t begin, clock_t end);

        void ReadTree  (const std::string& name_ast);
        void WriteTree (const std::string& name_ast);
};

//}==============================================================================

Compiler :: Compiler (InputInformation& scan):
    code        (),
    root        ({ Block }),
    file_source (fopen (scan.name_source.c_str (), "r")),
    file_asm    (fopen (scan.name_asm.c_str (), "w")),
    file_log    (scan.name_log.c_str ())
{
    Start ();
}

void Compiler :: Start (InputInformation& scan)
{
    LogBegin ();

    clock_t begin = clock ();

    Lexicial ();
    Preproc ();
    Syntax ();
    Semantic ();
    Optimize ();
    Generate ();

    clock_t end = clock ();

    LogEnd (begin, end);

    RenderTree (root, "..//Files//AST.dot", "..//Files//AST.jpg", false);
}

Compiler :: ~Compiler ()
{
    fclose (file_source);
    fclose (file_asm);
}

void Compiler :: LogBegin ()
{
    file_log.setFontColor ("white");
    file_log.setSize      (50);
    file_log.setColor     ("blue");

    file_log.setColor ("gray");
    file_log.output ("DeerC %d.%d\n\n", 1, 0);

    file_log.setColor ("blue");
    file_log.output ("========== Build started ==========\n");

    file_log.setColor ("red");
}

void Compiler :: LogEnd (clock_t begin, clock_t end)
{
    file_log.setColor ("blue");
    file_log.output ("========== Build finished ==========\n\n");

    file_log.setColor ("gray");
    file_log.output ("Build started on: %f\n",   (float) begin / CLOCKS_PER_SEC);
    file_log.output ("Build   ended on: %f\n\n", (float)   end / CLOCKS_PER_SEC);

    file_log.out ();
}

void Compiler :: ReadTree (const std::string& name_ast)
{
    FILE* ast = fopen (name_ast.c_str (), "r");

    assert (ast);

    root.read (ast);
}

void Compiler :: WriteTree (const std::string& name_ast)
{
    FILE* ast = fopen (name_ast.c_str (), "w");

    assert (ast);

    root.write (ast);

    fclose (ast);
}

void Compiler :: Preproc (bool flag)
{
    if (flag)
    {
        //Preprocessor preprocessor (code, file_log);
    }
}

void Compiler :: Lexicial (bool flag)
{
    if (flag)
    {
        LexicialAnalyzer lexicial_analyzer (file_source, code);
    }
}

void Compiler :: Syntax (bool flag)
{
    if (flag)
    {
        SyntaxAnalyzer syntax_analyzer (root, code, file_log);
    }
}

void Compiler :: Semantic (bool flag)
{
    if (flag)
    {
        //SemanticAnalyzer semantic_analyzer (root, file_log);
    }
}

void Compiler :: Optimize (bool flag)
{
    if (flag)
    {
        //Optimizer optimizer (root);
    }
}

void Compiler :: DisSyntax (bool flag)
{
    if (flag)
    {
        //Optimizer optimizer (root);
    }
}

void Compiler :: Generate (bool flag)
{
    if (flag)
    {
        CodeGeneration code_generation (root, file_asm, 1);
    }
}

void Compiler :: DisGenerator (bool flag)
{
    if (flag)
    {
        //Optimizer optimizer (root);
    }
}

#endif
