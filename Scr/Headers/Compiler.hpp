#ifndef Compiler_hpp
    #define Compiler_hpp

//SingleTon, dragonbook, static analysis, courses mail

//{==============================================================================

#include <ctime>
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

        void Start ();

        void Lexicial ();
        void Preproc ();
        void Syntax ();
        void Semantic ();
        void Optimize ();
        void Generate ();

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

void Compiler :: Start ()
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

void Compiler :: Lexicial ()
{
    LexicialAnalyzer lexicial_analyzer (file_source, code);
}

void Compiler :: Preproc ()
{
    //Preprocessor preprocessor (code, file_log);
}

void Compiler :: Syntax ()
{
    SyntaxAnalyzer syntax_analyzer (root, code, file_log);
}

void Compiler :: Semantic ()
{
    //SemanticAnalyzer semantic_analyzer (root, file_log);
}

void Compiler :: Optimize ()
{
    //Optimizer optimizer (root);
}

void Compiler :: Generate ()
{
    CodeGeneration code_generation (root, file_asm, 1);
}

#endif
