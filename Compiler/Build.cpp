//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Librarys//Debug.hpp"
#include "Librarys//Stream.hpp"
#include "Librarys//BinaryNode.hpp"
#include "Headers//FrontEnd//LexicialAnalyzer.hpp"
#include "Headers//FrontEnd//SyntaxAnalyzer.hpp"
#include "Headers//BackEnd//Compiler.hpp"
//#include "Headers//BackEnd//Assembler.hpp"

//}==============================================================================

using namespace std;

inline void Hello_C (string& example) { printf ("Input name of C file: "); cin >> example; }

int main (int argc, const char* argv[])
{
    try
    {
        //TRY

        string C_name;
        Hello_C (C_name);

        FILE* C_File = fopen (C_name.c_str (), "r");
        assert (C_File);

        Stream <char> example;

        for (char symbol = 0; fscanf (C_File, "%c", &symbol) != EOF;)
        {
            example.push_back (symbol);
        }

        Stream <Token> code;

        Parser (example, code);

        BinaryNode <Token> root;
        GetO (root, code);

        DotDump (root, "EX1.dot");

        FILE* asm_txt = fopen ("Data.txt", "w");

        CreateAsm (root, asm_txt);

        fclose (C_File);
        fclose (asm_txt);
    }
    catch (const char* message)
    {
        CATCH (message)
    }
    catch (...)
    {
        char message[1000];

        sprintf (message, "Unknown error was in %s\n", __PRETTY_FUNCTION__);

        CATCH (message)
    }

    return 0;
}
