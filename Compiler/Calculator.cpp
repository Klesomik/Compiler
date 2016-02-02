//ToDo: Rewrite dotter. Make class graph and crossplatform and russian language

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cassert>
#include "Headers//Vector.hpp"
#include "Headers//Stream.hpp"
#include "Parser.hpp"
#include "Headers//BinaryNode.hpp"
#include "GetLib.hpp"
#include "NewGetLib.hpp"

using namespace std;

void Scan (Vector <char>& tmp);
int CreateAsm (BinaryNode <Token>& current, FILE* write);

void FrontEnd ();
void BackEnd  ();

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

        FILE* asm_txt = fopen ("Asm.txt",  "w");

        BinaryNode <Token> root ();
                           root.copy (NewGetE (code));

        printf ("Result = %d\n", CreateAsm (root, asm_txt));

        fprintf (asm_txt, "eof;\n");

        fclose (asm_txt);

        N::DotDump (root, "EX1");
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
        char symbol = /*(char)*/ getchar ();

        if (symbol == '\n') break;

        tmp.push_back (symbol);
    }
}

int CreateAsm (BinaryNode <Token>& current, FILE* write)
{
    if (current.key ().type_ == Add)
    {
        int left =  CreateAsm (current.left  (), write);
        int right = CreateAsm (current.right (), write);

        fprintf (write, "add;\n");

        return (left + right);
    }

    else if (current.key ().type_ == Sub)
    {
        int left =  CreateAsm (current.left  (), write);
        int right = CreateAsm (current.right (), write);

        fprintf (write, "sub;\n");

        return (left - right);
    }

    else if (current.key ().type_ == Mul)
    {
        int left =  CreateAsm (current.left  (), write);
        int right = CreateAsm (current.right (), write);

        fprintf (write, "mul;\n");

        return (left * right);
    }

    else if (current.key ().type_ == Div)
    {
        int left =  CreateAsm (current.left  (), write);
        int right = CreateAsm (current.right (), write);

        fprintf (write, "div;\n");

        return (left / right);
    }

    else
    {
        fprintf (write, "push %d;\n", current.key ().value_);

        return current.key ().value_;
    }
}
