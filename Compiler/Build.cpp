#include "LexicialAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "Compiler.hpp"
#include "Assembler.hpp"

inline void Hello_C (string& example) { printf ("Input name of C file: "); cin >> example; }

int main (int argc, const char* argv[])
{
    try
    {
        string C_name;
        Hello_C (C_name);

        FileStream C_File (C_name, "r");
    }
    catch (const char* message)
    {
        CATCH(message)
    }
    catch (...)
    {
    }

    return 0;
}
