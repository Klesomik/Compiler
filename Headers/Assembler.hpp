#ifndef Assembler_hpp

#define Assembler_hpp

#include <cstdio>
#include <iostream>
#include "..//Libraries//Stream.hpp"
#include "BackEnd//BoaLexicialAnalyzer.hpp"
#include "BackEnd//BoaSyntaxAnalyzer.hpp"
#include "DisAssembler.hpp"

class Assembler
{
    public:
        Assembler ();

        void run (Stream <char>& asm_code, std::vector <int>& cpu_code);

    private:
        Stream <BoaToken> boa_token;

        Assembler (const Assembler& from);
        Assembler& operator = (const Assembler& from);
};

Assembler::Assembler ():
{
}

void Assembler::run (Stream <char>& asm_code, std::vector <int>& cpu_code)
{
    BoaLexicialAnalyzer lexicial;
                        lexicial.parsing (asm_code, boa_token);

    BoaSyntaxAnalyzer syntax;
                      syntax.parsing (boa_token, cpu_code);
}

#endif /* Assembler_hpp */
