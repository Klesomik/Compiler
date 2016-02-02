#include <cstdio>
#include "Parser.hpp"
#include "Headers//Stream.hpp"
#include "Headers//BinaryNode.hpp"

BinaryNode <Token>& NewGetN (Stream <Token>& example);
BinaryNode <Token>& NewGetP (Stream <Token>& example);
BinaryNode <Token>& NewGetT (Stream <Token>& example);
BinaryNode <Token>& NewGetE (Stream <Token>& example);

//{

// E = T | T + T | T - T
// T = P | P + P | P - P
// P = N | (E)   | -P
// N = {0; 1; 2; 3; 4; 5; 6; 7; 8; 9}

//}

BinaryNode <Token>& NewGetN (Stream <Token>& example)
{
    BinaryNode <Token> value;

    bool first = false;
    if (example.check () && example[example.place ()].type_ == Digit)
    {
        first = true;

        value.key () = example[example.place ()].value_;

        example++;
    }

    if (!first) throw "expected integer";

    return value;
}

BinaryNode <Token>& NewGetP (Stream <Token>& example)
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

        value.move (NewGetE (example));

        if (example.check () && example[example.place ()].type_ != Finish) throw "forget ')'";

        example++;
    }

    else
    {
        value.move (NewGetN (example));
    }

    return value;
}

BinaryNode <Token>& NewGetT (Stream <Token>& example)
{
    BinaryNode <Token> value;
                       value.move (NewGetP (example));

    while (example.check () && (example[example.place ()].type_ == Mul || example[example.place ()].type_ == Div))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insertLeft  (value);
                           operation.insertRight (NewGetP (example));

        value.move (operation);
    }

    return value;
}

BinaryNode <Token>& NewGetE (Stream <Token>& example)
{
    BinaryNode <Token> value;
                       value.move (NewGetT (example));

    while (example.check () && (example[example.place ()].type_ == Add || example[example.place ()].type_ == Sub))
    {
        int sign = example[example.place ()].type_;

        example++;

        BinaryNode <Token> operation ({ sign, 0 });
                           operation.insertLeft  (value);
                           operation.insertRight (NewGetT (example));

        value.move (operation);
    }

    return value;
}
