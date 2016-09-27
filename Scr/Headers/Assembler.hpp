#ifndef Assembler_hpp
    #define Assembler_hpp

#include <cstdio>
#include "..//Libraries//Stream.hpp"
#include "BackEnd//BoaLexicialAnalyzer.hpp"
#include "BackEnd//BoaSyntaxAnalyzer.hpp"

class Assembler
{
    private:
        FILE* boa;
        FILE* bit;

    public:
        Assembler (const std::string& name_asm, const std::string& name_byte);
        ~Assembler ();
};

Assembler :: Assembler (const std::string& name_asm, const std::string& name_byte):
    boa (fopen (name_asm.c_str (), "r")),
    bit (fopen (name_byte.c_str (), "w"))
    {
        Stream <BoaToken> code;

        BoaLexicialAnalyzer lexicial;
        lexicial.read (boa);
        lexicial.parser (code);

        BoaSyntaxAnalyzer syntax;
        syntax.read (code);
        syntax.write (bit);
    }

Assembler :: ~Assembler ()
{
    fclose (boa);
    fclose (bit);
}

#endif
