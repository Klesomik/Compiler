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

// Z = O | { Z }
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

void GetZ (BinaryNode <Token>* current, Stream <Token>& example)
{
    while (example.check ())
    {
        if (example[example.place ()].type_ == Begin)
        {
            while (example.check () && example[example.place ()].type_ == Begin)
            {
                example++;

                GetZ (current, example);

                char end = 0;
                example >> end;

                if (end != End) THROW ("Expected '}'");

                GetZ (current, example);
            }
        }

        else
        {
            Vector <char> tmp;

            while (example.check () && example[example.place ()].type_ != EndOfToken)
            {
                tmp.push_back (symbol);

                char symbol = 0;
                example >> symbol;
            }

            Stream <char> command (tmp);

            BinaryNode <Token> value;
            GetO (value, command);

            current -> insertLeft  (value);
            current -> insertRight ();

            GetZ (current -> right (), example);
        }
    }
}
