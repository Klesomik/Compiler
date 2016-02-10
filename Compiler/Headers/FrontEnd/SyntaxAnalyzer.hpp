#pragma once

#include <cstdio>
#include "LexicialAnalyzer.hpp"
#include "..//..//Librarys//Debug.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "..//..//Librarys//AbstractSyntaxTree.hpp"

void GetN (BinaryNode <Token>& current, Stream <Token>& example);
void GetW (BinaryNode <Token>& current, Stream <Token>& example);
void GetP (BinaryNode <Token>& current, Stream <Token>& example);
void GetT (BinaryNode <Token>& current, Stream <Token>& example);
void GetE (BinaryNode <Token>& current, Stream <Token>& example);
void GetO (BinaryNode <Token>& current, Stream <Token>& example);
void GetZ (BinaryNode <Token>& current, Stream <Token>& example);

//{

// O = E | E = E
// E = T | T + T | T - T
// T = P | P + P | P - P
// P = N | (O)   | -P
// N = ['0'-'9']
// W = ['a'-'z']

//}

void GetN (BinaryNode <Token>& current, Stream <Token>& example)
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

void GetW (BinaryNode <Token>& current, Stream <Token>& example)
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

void GetP (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;

    if (example.check () && example[example.place ()].type_ == Sub)
    {
        example++;

        //value = -GetP (example); *-1
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
        GetN (value, example);
    }

    current.move (value);
}

void GetT (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;
    GetP (value, example);

    while (example.check () && (example[example.place ()].type_ == Mul || example[example.place ()].type_ == Div))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insert (value);

                           GetP (value, example);
                           operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetE (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;
    GetT (value, example);

    while (example.check () && (example[example.place ()].type_ == Add || example[example.place ()].type_ == Sub))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insert (value);

                           GetT (value, example);
                           operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetO (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;
    GetE (value, example);

    while (example.check () && example[example.place ()].type_ == Equal)
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insert (value);

                           GetE (value, example);
                           operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetZ (BinaryNode <Token>& current, Stream <Token>& example)
{
    if (example.check ())
    {
        if (example[example.place ()].type_ == Begin)
        {
            while (example.check () && example[example.place ()].type_ == Begin)
            {
                example++; //{

                BinaryNode <Token> grayNode ({ None, None });

                GetZ (grayNode, example);

                current.insert (grayNode);

                example++; //}
            }
        }

        else
        {
            while (example.check () && example[example.place ()].type_ != End)
            {
                Stream <Token> tmp;

                while (example.check () && example[example.place ()].type_ != EndOfToken)
                {
                    tmp.push_back (example[example.place ()]);

                    example++;
                }

                BinaryNode <Token> operation;

                GetO (operation, tmp);

                current.insert (operation);

                example++;
            }
        }
    }
}
