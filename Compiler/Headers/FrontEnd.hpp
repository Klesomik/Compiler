#include <cstdio>
#include "Parser.hpp"
#include "Headers//Stream.hpp"
#include "Headers//BinaryNode.hpp"

void GetNumber (BinaryNode <Token>& current, Stream <Token>& example);
void GetP (BinaryNode <Token>& current, Stream <Token>& example);
void GetT (BinaryNode <Token>& current, Stream <Token>& example);
void GetE (BinaryNode <Token>& current, Stream <Token>& example);
void GetOparator ();

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

    if (!first) throw "expected integer";
}

void GetP (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;

    if (example.check () && example[example.place ()].type_ == Sub)
    {
        example++;

        //value = -NewGetP (example); *-1
    }

    else if (example.check () && example[example.place ()].type_ == Start)
    {
        example++;

        NewGetE (value, example);

        if (example.check () && example[example.place ()].type_ != Finish) throw "forget ')'";

        example++;
    }

    else
    {
        NewGetN (value, example);
    }

    current.move (value);
}

void GetT (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;
    NewGetP (value, example);

    while (example.check () && (example[example.place ()].type_ == Mul || example[example.place ()].type_ == Div))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insertLeft  (value);

                           NewGetP (value, example);
                           operation.insertRight (value);

        value.move (operation);
    }

    current.move (value);
}

void GetE (BinaryNode <Token>& current, Stream <Token>& example)
{
    BinaryNode <Token> value;
    NewGetT (value, example);

    while (example.check () && (example[example.place ()].type_ == Add || example[example.place ()].type_ == Sub))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insertLeft  (value);

                           NewGetT (value, example);
                           operation.insertRight (value);

        value.move (operation);
    }

    current.move (value);
}
