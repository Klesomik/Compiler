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

        FILE* file_c;
        FILE* file_asm;

        LogHTML file_log;

        Compiler (const Compiler& from);
        Compiler& operator = (const Compiler& from);

    public:
        Compiler (const std::string& name_c,
                  const std::string& name_asm,
                  const std::string& name_log,
                  const std::string& name_dot,
                  const std::string& name_graph,
                  const std::string& name_ast);

        ~Compiler ();

        void Start (const std::string& name_dot, const std::string& name_graph, const std::string& name_ast);

        void LogBegin (LogHTML& log);
        void LogEnd (LogHTML& log, clock_t begin, clock_t end);

        void ReadTree  (const std::string& name_ast);
        void WriteTree (const std::string& name_ast);
};

//}==============================================================================

Compiler :: Compiler (const std::string& name_c,
                      const std::string& name_asm,
                      const std::string& name_log,
                      const std::string& name_dot,
                      const std::string& name_graph,
                      const std::string& name_ast):
    code       (),
    root       ({ Block }),
    file_c     (fopen (name_c.c_str (), "r")),
    file_asm   (fopen (name_asm.c_str (), "w")),
    file_log   (name_log.c_str ())
{
    Start (name_dot, name_graph, name_ast);
}

void Compiler :: Start (const std::string& name_dot, const std::string& name_graph, const std::string& name_ast)
{
    LogBegin (file_log);

    clock_t begin = clock ();

    //ReadTree (name_ast);

    LexicialAnalyzer lexicial_analyzer (file_c, code);
    //Preprocessor          preprocessor (code, file_log);
    SyntaxAnalyzer     syntax_analyzer (root, code, file_log);
    //SemanticAnalyzer semantic_analyzer (root, file_log);
    //Optimizer                optimizer (root);
    CodeGeneration     code_generation (root, file_asm, 1);

    RenderTree (root, name_dot, name_graph, false);

    //WriteTree (name_ast);

    clock_t end = clock ();

    LogEnd (file_log, begin, end);
}

Compiler :: ~Compiler ()
{
    fclose (file_c);
    fclose (file_asm);
}

void Compiler :: LogBegin (LogHTML& log)
{
    log.setFontColor ("white");
    log.setSize      (50);
    log.setColor     ("blue");

    log.setColor ("gray");
    log.output ("DeerC %d.%d\n\n", 1, 0);

    log.setColor ("blue");
    log.output ("========== Build started ==========\n");

    log.setColor ("red");
}

void Compiler :: LogEnd (LogHTML& log, clock_t begin, clock_t end)
{
    log.setColor ("blue");
    log.output ("========== Build finished ==========\n\n");

    log.setColor ("gray");
    log.output ("Build started on: %f\n",   (float) begin / CLOCKS_PER_SEC);
    log.output ("Build   ended on: %f\n\n", (float)   end / CLOCKS_PER_SEC);

    log.out ();
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

#endif
