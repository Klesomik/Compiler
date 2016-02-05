#include <cstdio>
#include "LexicialAnalyzer.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "..//..//Librarys//BinaryNode.hpp"

void GetN (BinaryNode <Token>& current, Stream <Token>& example);
void GetP (BinaryNode <Token>& current, Stream <Token>& example);
void GetT (BinaryNode <Token>& current, Stream <Token>& example);
void GetE (BinaryNode <Token>& current, Stream <Token>& example);
void GetO (BinaryNode <Token>& current, Stream <Token>& example);

//{

// E = T | T + T | T - T
// T = P | P + P | P - P
// P = N | (E)   | -P
// N = {0; 1; 2; 3; 4; 5; 6; 7; 8; 9}

//}

void GetN (BinaryNode <Token>& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && example[example.place ()].type_ == Digit)
    {
        first = true;

        current.key () = example[example.place ()].value_;

        example++;
    }

    if (!first) THROW ("expected integer");
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

        GetE (value, example);

        if (example.check () && example[example.place ()].type_ != Finish) THROW ("forget ')'");

        example++;
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
                           operation.insertLeft  (value);

                           GetP (value, example);
                           operation.insertRight (value);

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
                           operation.insertLeft  (value);

                           GetT (value, example);
                           operation.insertRight (value);

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
                           operation.insertLeft  (value);

                           GetE (value, example);
                           operation.insertRight (value);

        value.move (operation);
    }

    current.move (value);
}