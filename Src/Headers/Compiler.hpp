#ifndef Compiler_hpp

#define Compiler_hpp

#include <cstdio>
#include <ctime>
#include <iostream>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//AbstractSyntaxNode.hpp"
#include "..//Libraries//LogHTML.hpp"
#include "FrontEnd//LexicialAnalyzer.hpp"
//#include "FrontEnd//Preprocessor.hpp"
//#include "FrontEnd//SyntaxAnalyzer.hpp"
//#include "FrontEnd//SemanticAnalyzer.hpp"
//#include "FrontEnd//Optimizer.hpp"
//#include "FrontEnd//CodeGeneration.hpp"

class Compiler
{
    public:
        Compiler ();

        ~Compiler ();

        void run (Stream <char>& to);

        void Lexicial     (Stream <char>& from, Stream <Token>& to);
        void Preproc      (Stream <Token>& from);
        void Syntax       (Stream <Token>& from, AstNode& to);
        void Semantic     (AstNode& from);
        void Optimize     (AstNode& from);
        void DisSyntax    (AstNode& from, Stream <Token>& to);
        void Generate     (AstNode& from, Stream <char>& to);
        void DisGenerator (Stream <char>& from, AstNode& to);

        /*Stream <char>& first ();
        Stream <Token>& second ();
        AstNode& root ();
        LogHTML& log ();*/

    //private:
        Stream <char> first;   // code_c
        Stream <Token> second; // token_c

        AstNode root;

        LogHTML log_;

        clock_t begin, end;

        Compiler (const Compiler& from);
        Compiler& operator = (const Compiler& from);

        void log_begin (LogHTML& log, const char* version);
        void log_end (LogHTML& log, clock_t begin, clock_t end);
        void log_error (LogHTML& log, const char* message);
};

Compiler::Compiler ():
    first  (),
    second (),
    root   ({ Block }),
    log_   ("Log.html"),
    begin  (clock ()),
    end    ()
{
    log_begin (log_, "1.0");
}

Compiler::~Compiler ()
{
    //log_.picture ();

    log_end (log_, begin, end);
}

void Compiler::run (Stream <char>& to)
{
    Lexicial (first, second);
    Preproc  (second);
    Syntax   (second, root);
    Semantic (root);
    Optimize (root); //
    Generate (root, to);
}

void Compiler::Lexicial (Stream <char>& from, Stream <Token>& to)
{
    CAP::LexicialAnalyzer lexicial;

    lexicial.parsing (from, to);
}

void Compiler::Preproc (Stream <Token>& from)
{
    /*CAP::Preprocessor preprocessor (code, log_);

    preprocessor.parsing ();*/
}

void Compiler::Syntax (Stream <Token>& from, AstNode& to)
{
    /*CAP::SyntaxAnalyzer syntax;

    syntax.parsing (from, to, log_);*/
}

void Compiler::DisSyntax (AstNode& from, Stream <Token>& to)
{
    /*CAP::DisSyntax dis_syntax;

    dis_syntax.parsing ();*/
}

void Compiler::Semantic (AstNode& from)
{
    /*CAP::SemanticAnalyzer semantic_analyzer (root, log_);

    semantic_analyzer.parsing ();*/
}

void Compiler::Optimize (AstNode& from)
{
    /*CAP::Optimizer optimizer (root);

    optimizer.parsing ();*/
}

void Compiler::Generate (AstNode& from, Stream <char>& to)
{
    /*CAP::CodeGeneration code_generation (root, file_asm, 1);

    code_generation.parsing ();*/
}

void Compiler::DisGenerator (Stream <char>& from, AstNode& to)
{
    /*CAP::DisGenerator dis_generator;

    dis_generator.parsing ();*/
}

/*Stream <char>& Compiler::first ()
{
    return first;
}

Stream <Token>& Compiler::second ()
{
    return second;
}

AstNode& Compiler::root ()
{
    return root;
}

LogHTML& Compiler::log ()
{
    return log_;
}*/

void Compiler::log_begin (LogHTML& log, const char* version)
{
    log.setFontColor ("white");
    log.setSize      (50);
    log.setColor     ("blue");

    log.setColor ("gray");
    log.output ("DeerC %s\n\n", version);

    log.setColor ("blue");
    log.output ("========== Build started ==========\n");

    log.setColor ("red");
}

void Compiler::log_end (LogHTML& log, clock_t begin, clock_t end)
{
    log.setColor ("blue");
    log.output ("========== Build finished ==========\n\n");

    log.setColor ("gray");
    log.output ("Build started on: %f\n",   (float) begin / CLOCKS_PER_SEC);
    log.output ("Build   ended on: %f\n\n", (float)   end / CLOCKS_PER_SEC);
}

void Compiler::log_error (LogHTML& log, const char* message)
{
    log.output (message);

    throw message;
}

#endif /* Compiler_hpp */
