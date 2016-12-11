#ifndef Compiler_hpp
    #define Compiler_hpp

#include <cstdio>
#include <ctime>
#include <iostream>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//AbstractSyntaxNode.hpp"
#include "..//Libraries//LogHTML.hpp"
#include "InputInformation.hpp"
#include "FrontEnd//LexicialAnalyzer.hpp"
//#include "FrontEnd//Preprocessor.hpp"
#include "FrontEnd//SyntaxAnalyzer.hpp"
#include "FrontEnd//SemanticAnalyzer.hpp"
#include "FrontEnd//Optimizer.hpp"
#include "FrontEnd//CodeGeneration.hpp"

class Compiler
{
    public:
        Compiler (const InputInformation& scan);

        ~Compiler ();

        void run (const InputInformation& scan, Stream <char>& to);

        void Lexicial     ();
        void Preproc      ();
        void Syntax       ();
        void Semantic     ();
        void Optimize     ();
        void DisSyntax    ();
        void Generate     ();
        void DisGenerator ();

    private:
        Stream <char> first;   // code_c
        Stream <Token> second; // token_c

        AstNode root;

        LogHTML file_log;

        Compiler (const Compiler& from);
        Compiler& operator = (const Compiler& from);
};

Compiler::Compiler (const InputInformation& scan):
    first    (),
    second   (),
    root     ({ Block }),
    file_log (scan.name_log.c_str ())
{
}

void Compiler::run (const InputInformation& scan, Stream <char>& to)
{
    if (scan.log)
    {
        LogBegin ();
        clock_t begin = clock ();
    }

    ScanFile (first, scan.name_source);

    if (scan.lexicial) Lexicial (first, second);
    if (scan.preprocessor) Preproc (second);
    if (scan.syntax) Syntax   (second, root);
    if (scan.semantic) Semantic (root);
    if (scan.optimiser) Optimize (root); //
    if (scan.generator) Generate (root, to);

    if (scan.log)
    {
        clock_t end = clock ();
        LogEnd (begin, end);
    }
}

void Compiler::Preproc ()
{
    //Preprocessor preprocessor (code, file_log);
}

void Compiler::Lexicial ()
{
    LexicialAnalyzer lexicial_analyzer (file_source, code);
}

void Compiler::Syntax ()
{
    SyntaxAnalyzer syntax_analyzer (root, code, file_log);
}

void Compiler::Semantic ()
{
    //SemanticAnalyzer semantic_analyzer (root, file_log);
}

void Compiler::Optimize ()
{
    //Optimizer optimizer (root);
}

void Compiler::DisSyntax ()
{
}

void Compiler::Generate ()
{
    CodeGeneration code_generation (root, file_asm, 1);
}

void Compiler::DisGenerator ()
{
}

#endif
