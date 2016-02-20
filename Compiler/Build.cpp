//Include
//{==============================================================================

//#include <ctype.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "Librarys//Debug.hpp"
#include "Librarys//Stream.hpp"
#include "Librarys//AbstractSyntaxTree.hpp"
#include "Headers//FrontEnd//LexicialAnalyzer.hpp"
#include "Headers//FrontEnd//SyntaxAnalyzer.hpp"

//}==============================================================================

using namespace std;

inline void Hello_C (std::string& example) { printf ("Input name of C file: "); std::cin >> example; }

int main (int argc, const char* argv[])
{
    try
    {
        TRY

        std::string C_name;
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

        AstNode root ({ None, None });
        GetBlock (root, code);

        DotDump (root, "EX1.dot");

        fclose (C_File);
    }
    catch (const char* message)
    {
        CATCH
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}
