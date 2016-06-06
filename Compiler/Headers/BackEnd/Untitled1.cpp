#include "BoaLexicialAnalyzer.hpp"
#include "BoaSyntaxAnalyzer.hpp"
#include "..//Cpu.hpp"

int main ()
{
    try
    {
        FILE* data = fopen ("Data.txt", "r");
        Stream <BoaToken> code;
        BoaLexicialAnalyzer lexicial;
        lexicial.read (data);
        lexicial.parser (code);
        fclose (data);

        FILE* bit = fopen ("Bit.txt", "w");
        BoaSyntaxAnalyzer syntax;
        syntax.read (code);
        syntax.write (bit);
        fclose (bit);

        FILE* result = fopen ("Bit.txt", "r");
        Cpu cpu;
        cpu.read (result);
        cpu.play ();
        fclose (result);
    }
    catch (const char* message)
    {
        std::cout << message;
    }

    return 0;
}
