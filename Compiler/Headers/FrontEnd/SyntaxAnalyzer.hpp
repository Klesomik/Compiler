#ifndef SYNTAX_INCLUDED
    #define SYNTAX_INCLUDED

#include <cstdio>
#include "LexicialAnalyzer.hpp"
#include "..//..//Librarys//Debug.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "..//..//Librarys//AbstractSyntaxTree.hpp"

//Change names

void GetNumber (AstNode& current, Stream <Token>& example);
void GetW      (AstNode& current, Stream <Token>& example);
void GetP      (AstNode& current, Stream <Token>& example);
void GetT      (AstNode& current, Stream <Token>& example);
void GetE      (AstNode& current, Stream <Token>& example);
void GetEqual  (AstNode& current, Stream <Token>& example);
void GetO      (AstNode& current, Stream <Token>& example);
void GetLexem  (AstNode& current, Stream <Token>& example);
void GetBlock  (AstNode& current, Stream <Token>& example);

//{

// Block = { [Lexem] }
// Lexem = O; | B
// O     = Equal | W = O
// Equal = E | E == E
// E     = T | T + T | T - T
// T     = P | P * P | P / P
// P     = N | W     | (O)   | -P | +P
// N     = ['0'-'9']
// W     = ['a'-'z']

//}

void GetNumber (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && example[example.place ()].type_ == Digit)
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first) THROW ("expected integer");
}

void GetW (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && example[example.place ()].type_ == Var)
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first) THROW ("expected name of variable");
}

void GetP (AstNode& current, Stream <Token>& example)
{
    AstNode value; //else with out; throw

    if (example.check () && example[example.place ()].type_ == Sub)
    {
        example++;

        //value = -GetP (example); *-1
    }

    else if (example.check () && example[example.place ()].type_ == Add)
    {
        example++;

        //value = +GetP (example); *+1
    }

    else if (example.check () && example[example.place ()].type_ == Start)
    {
        example++;

        GetO (value, example);

        if (example.check () && example[example.place ()].type_ != Finish) THROW ("forgot ')'");

        example++;
    }

    else if (example.check () && example[example.place ()].type_ == Var)
    {
        GetW (value, example);
    }

    else
    {
        GetNumber (value, example);
    }

    current.move (value);
}

void GetT (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetP (value, example);

    while (example.check () && (example[example.place ()].type_ == Mul || example[example.place ()].type_ == Div))
    {
        int sign = example[example.place ()].type_;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetP (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetE (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetT (value, example);

    while (example.check () && (example[example.place ()].type_ == Add || example[example.place ()].type_ == Sub))
    {
        int sign = example[example.place ()].type_;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetT (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetEqual (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetE (value, example);

    while (example.check () && example[example.place ()].type_ == EqualEqual)
    {
        int sign = example[example.place ()].type_;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetE (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetO (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetEqual (value, example);

    while (example.check () && example[example.place ()].type_ == Equal)
    {
        int sign = example[example.place ()].type_;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetE (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetLexem (AstNode& current, Stream <Token>& example)
{
    Stream <Token> tmp;

    if (example.check ())
    {
        if (example[example.place ()].type_ == Begin)
        {
            AstNode grayNode ({ None, None }); //

            GetBlock (grayNode, example);

            current.insert (grayNode);
        }

        else
        {
            AstNode operation;

            while (example.check () && example[example.place ()].type_ != EndOfToken)
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            GetO (operation, tmp);

            current.insert (operation);

            example++;
        }
    }
}

void GetBlock (AstNode& current, Stream <Token>& example)
{
    if (example.check () && example[example.place ()].type_ == Begin)
    {
        example++;

        //AstNode grayNode ({ None, None });

        while (example.check () && example[example.place ()].type_ != End)
            GetLexem (current, example); //grayNode

        //current.insert (grayNode);

        example++;
    }

    else throw "expected '{'";
}

#endif
