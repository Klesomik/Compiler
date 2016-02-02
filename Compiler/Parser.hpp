#ifndef PARSER_HPP_INCLUDED
    #define PARSER_HPP_INCLUDED

#include <iostream>
#include <cstring>
#include <map>
#include "Headers//Stream.hpp"

using namespace std;

typedef unsigned char flag;

enum Operations
{
    Digit = 0,
    Add,
    Sub,
    Mul,
    Div,
    Start,
    Finish
};

map <flag, int> Table = { { '+',    Add },
                          { '-',    Sub },
                          { '*',    Mul },
                          { '/',    Div },
                          { '(',  Start },
                          { ')', Finish } };

//{==============================================================================

struct Token
{
    int type_;

    int value_;

    Token ();
    Token (int  token);
    Token (char token);
    Token (int typeVal, int valueVal);
};

//}==============================================================================

Token :: Token ():
    type_  (),
    value_ ()
    {}

Token :: Token (int token):
    type_  (Digit),
    value_ (token)
    {}

Token :: Token (char token):
    type_  (Table[token]),
    value_ (0)
    {}

Token :: Token (int typeVal, int valueVal):
    type_  (typeVal),
    value_ (valueVal)
    {}

void SkipSpace (Stream <char>& example);
void Parser    (Stream <char>& example, Stream <Token>& code);

void SkipSpace (Stream <char>& example)
{
    while (example.check () && example[example.place ()] == ' ')
    {
        char digit = 0;
        example >> digit;
    }
}

void Parser (Stream <char>& example, Stream <Token>& code)
{
    while (example.check ())
    {
        SkipSpace (example);

        if ('0' <= example[example.place ()] || '9' <= example[example.place ()])
        {
            int value = 0;

            while (example.check () && ('0' <= example[example.place ()] || '9' <= example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value = value * 10 + digit - '0';
            }

            Token tmp (value);

            code.push_back (tmp);
        }

        else
        {
            char symbol = 0;
            example >> symbol;

            Token tmp (symbol);

            code.push_back (tmp);
        }
    }
}

#endif /* PARSER_HPP_INCLUDED */
