//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Librarys//Debug.hpp"
#include "Librarys//Stream.hpp"
#include "Headers//FrontEnd//DeerLib.hpp"
#include "Librarys//AbstractSyntaxTree.hpp"
#include "Headers//FrontEnd//Compiler.hpp"
#include "Headers//FrontEnd//Optimizer.hpp"

//}==============================================================================

using namespace std;

//{==============================================================================

//void AsmGenerate (AstNode& root);

//}==============================================================================

int main (int argc, const char* argv[])
{
    try
    {
        Stream <Token> code;

        LexicialAnalyzer lexicial_analyzer (code);

        code.dump ();

        AstNode root ({ None, None });

        Compiler compiler (root, code);

        Optimizer optimizer (root);

        //AsmGenerate (root);

        DotDump (root, "EX1.dot");
    }
    catch (std::exception)
    {
    }
    catch (const char* message)
    {
        CATCH
    }
    catch (const int message)
    {
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}

//===============================================================================

/*void AsmGenerate (AstNode& root)
{
    std::string Asm_name;
    Hello_Asm (Asm_name);

    FILE* asm_code = fopen (Asm_name.c_str (), "w");
    assert (asm_code);

    fprintf (asm_code, "jmp main;\n");
    fprintf (asm_code, "label main;\n");

    for (size_t i = 0; i < root.children ().size (); i++)
        CreateAsm (root.children ()[i], asm_code);

    fprintf (asm_code, "eof;\n");

    fclose (asm_code);
}*/
