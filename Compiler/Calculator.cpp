#include "TXLib.h"
#include "Parser.hpp"
#include "FrontEnd.hpp"
#include "BackEnd.hpp"

using namespace std;

void Scan (Vector <char>& tmp);

int main ()
{
    try
    {
        printf ("This program creates instance tree and calculate result.\nPlease, put instance: ");

        Vector <char> tmp;
        Scan (tmp);

        Stream <char> example (tmp);

        Stream <Token> code;
        Parser (example, code);

        BinaryNode <Token> root;
                           root.move (NewGetE (code));

        //printf ("Result = %d\n", CreateAsm (root, asm_txt));

        //DotDump (root, "EX1.dot");
    }
    catch (const char* message)
    {
        printf ("ERROR: %s\n", message);
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}

void Scan (Vector <char>& tmp)
{
    while (true)
    {
        char symbol = getchar ();

        if (symbol == '\n') break;

        tmp.push_back (symbol);
    }
}
