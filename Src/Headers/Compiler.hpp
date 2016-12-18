#ifndef Compiler_hpp
    #define Compiler_hpp

#include <cstdio>
#include <ctime>
#include <iostream>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//AbstractSyntaxNode.hpp"
#include "..//Libraries//LogHTML.hpp"
//#include "InputInformation.hpp"
//#include "FrontEnd//LexicialAnalyzer.hpp"
//#include "FrontEnd//Preprocessor.hpp"
//#include "FrontEnd//SyntaxAnalyzer.hpp"
//#include "FrontEnd//SemanticAnalyzer.hpp"
//#include "FrontEnd//Optimizer.hpp"
//#include "FrontEnd//CodeGeneration.hpp"

class Compiler
{
    public:
        Compiler (const InputInformation& scan);

        ~Compiler ();

        void run (const InputInformation& scan, Stream <char>& to);

        void Lexicial     (Stream <char>& from, Stream <Token>& to);
        void Preproc      (Stream <Token>& from);
        void Syntax       (Stream <Token>& from, AstNode& to);
        void Semantic     (AstNode& from);
        void Optimize     (AstNode& from);
        void DisSyntax    (AstNode& from, Stream <Token>& to);
        void Generate     (AstNode& from, Stream <char>& to);
        void DisGenerator (Stream <char>& from, AstNode& to);

    private:
        Stream <char> first;   // code_c
        Stream <Token> second; // token_c

        AstNode root;

        LogHTML log_;

        clock_t begin, end;

        Compiler (const Compiler& from);
        Compiler& operator = (const Compiler& from);
};

Compiler::Compiler (const InputInformation& scan):
    first  (),
    second (),
    root   ({ Block }),
    log_   (scan.name_log.c_str ()),
    begin  (clock ()),
    end    ()
{
    LogBegin (log_, "1.0");
}

Compiler::~Compiler ()
{
    LogEnd (log_, begin, end);
}

void Compiler::run (const InputInformation& scan, Stream <char>& to)
{
    ScanFile (first, scan.name_source);

    if (scan.lexicial) Lexicial (first, second);
    if (scan.preprocessor) Preproc (second);
    if (scan.syntax) Syntax   (second, root);
    if (scan.semantic) Semantic (root);
    if (scan.optimiser) Optimize (root); //
    if (scan.generator) Generate (root, to);
}

void Compiler::Lexicial (Stream <char>& from, Stream <Token>& to)
{
    //LexicialAnalyzer lexicial;

    //lexicial.parsing (from, to);
}

void Compiler::Preproc (Stream <Token>& from)
{
    //Preprocessor preprocessor (code, log_);
}

void Compiler::Syntax (Stream <Token>& from, AstNode& to)
{
    //SyntaxAnalyzer syntax;

    //syntax.parsing (from, to, log_);
}

void Compiler::DisSyntax (AstNode& from, Stream <Token>& to)
{
}

void Compiler::Semantic (AstNode& from)
{
    //SemanticAnalyzer semantic_analyzer (root, log_);
}

void Compiler::Optimize (AstNode& from)
{
    //Optimizer optimizer (root);
}

void Compiler::Generate (AstNode& from, Stream <char>& to)
{
    //CodeGeneration code_generation (root, file_asm, 1);
}

void Compiler::DisGenerator (Stream <char>& from, AstNode& to)
{
}

#endif
