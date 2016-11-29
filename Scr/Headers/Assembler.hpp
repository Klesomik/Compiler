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
    private:
        FILE* boa;
        FILE* bit;

        Assembler (const Assembler& from);
        Assembler& operator = (const Assembler& from);

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

        Stream <int> in;

        GetLine (in, '\0');

        DisAssembler ();
    }

Assembler :: ~Assembler ()
{
    fclose (boa);
    fclose (bit);
}

#endif
