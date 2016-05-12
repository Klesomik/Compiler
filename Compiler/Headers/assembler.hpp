#ifndef Assembler_hpp
    #define Assembler_hpp

#include <cstdio>
#include "..//Librarys//Stream.hpp"
#include "BackEnd//BoaLexicialAnalyzer.hpp"
#include "BackEnd//BoaSyntaxAnalyzer.hpp"

class Assembler
{
    public:
        Assembler (FILE* boa, FILE* bit);
};

Assembler :: Assembler (FILE* boa, FILE* bit)
    {
        Stream <BoaToken> code;

        BoaLexicialAnalyzer lexicial;
        lexicial.read (boa);
        lexicial.parser (code);

        BoaSyntaxAnalyzer syntax;
        syntax.read (code);
        syntax.write (bit);
    }

#endif
