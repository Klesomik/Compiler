#ifndef PARSER_HPP_INCLUDED
    #define PARSER_HPP_INCLUDED

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"

using namespace std;

typedef unsigned char flag;

enum Operations
{
    Digit = 0,
    Var,
    Add,
    Sub,
    Mul,
    Div,
    Start,
    Finish,
    Equal,
    Begin,
    End,
    EqualEqual,
    If,
    Else
};

map <flag, int> Table = { { '+',    Add },
                          { '-',    Sub },
                          { '*',    Mul },
                          { '/',    Div },
                          { '(',  Start },
                          { ')', Finish },
                          { '=',  Equal },
                          { '{',  Begin },
                          { '}',    End } };

Vector <string> Variables;

//{==============================================================================

struct Token
{
    int type_;

    int value_;

    Token ();
    Token (int     token);
    Token (char    token);
    Token (string& token);
    Token (int typeVal, int valueVal);

    std::ostream& operator << (std::ostream& os);
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

Token :: Token (string& token):
    type_  (Var),
    value_ ()
    {
        bool first = false;
        for (size_t i = 0; i < Variables.size (); i++)
        {
            if (Variables[i] == token)
            {
                value_ = i;

                first = true;

                break;
            }
        }

        if (!first)
        {
            Variables.push_back (token);

            value_ = Variables.size () - 1;
        }
    }

Token :: Token (int typeVal, int valueVal):
    type_  (typeVal),
    value_ (valueVal)
    {}

std::ostream& Token :: operator << (std::ostream& os)
{
    return os << type_ << " " << value_;
}

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

        if ('0' <= example[example.place ()] && '9' >= example[example.place ()])
        {
            int value = 0;

            while (example.check () && ('0' <= example[example.place ()] && '9' >= example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value = value * 10 + digit - '0';
            }

            Token tmp (value);

            code.push_back (tmp);
        }

        else if ('a' <= example[example.place ()] && 'z' >= example[example.place ()])
        {
            string value;

            while (example.check () && ('a' <= example[example.place ()] && 'z' >= example[example.place ()]))
            {
                char symbol = 0;
                example >> symbol;

                value.push_back (symbol);
            }

            if (value == "if")
            {
                Token tmp (If, 0);

                code.push_back (tmp);
            }

            else if (value == "else")
            {
                Token tmp (Else, 0);

                code.push_back (tmp);
            }

            else
            {
                Token tmp (value);

                code.push_back (tmp);
            }
        }

        else if ('=' == example[example.place ()])
        {
            char sign = 0;
            example >> sign;

            if (example.check () && '=' == example[example.place ()])
            {
                Token tmp (EqualEqual, 0);

                code.push_back (tmp);
            }

            else
            {
                Token tmp (Equal, 0);

                code.push_back (tmp);
            }
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
