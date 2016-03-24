#ifndef Assembler_hpp
    #define Assembler_hpp

#include "FrontEnd//CodeGeneration.hpp"
#include "BackEnd//ByteGeneration.hpp"

class Assembler
{
    public:
        Assembler (AstNode& root, FILE* boa, FILE* bit);
};

Assembler :: Assembler (AstNode& root, FILE* boa, FILE* bit)
    {
        CodeGeneration code_generation (root, boa);

        ByteGeneration byte_generation (boa, bit);
    }

#endif
