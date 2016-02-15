#pragma once

//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"

//}==============================================================================

using namespace std;

//{==============================================================================

enum Lexemes
{
    Digit = 0,
    Var,

    //Operators:
    OpenBracket,
    CloseBracket,
    Mul,
    Div,
    Mod,
    Add,
    Sub,
    Equal,
    NotEqual,
    And,
    Or,
    Assignment,

    //SpecialSymbols:
    Begin,
    End,
    EndOfToken,

    //KeyWords:
    If,
    Else,

    //None:
    None
};

//}==============================================================================

//{==============================================================================

map <string, int> SpecialSymbols = { { "{",      Begin },
                                     { "}",        End },
                                     { ";", EndOfToken }, };

map <string, int> Operators = { {  "(",  OpenBracket },
                                {  ")", CloseBracket },
                                {  "*",          Mul },
                                {  "/",          Div },
                                {  "%",          Mod },
                                {  "+",          Add },
                                {  "-",          Sub },
                                { "==",        Equal },
                                { "!=",     NotEqual },
                                { "&&",          And },
                                { "||",           Or },
                                {  "=",   Assignment } };

map <string, int> KeyWords = { {   "if",   If },
                               { "else", Else } };

map <string, int> Names = {};

//}==============================================================================

//{==============================================================================

struct Token
{
    int type_;  //type
    int value_; //value
                //polimorfizm

    Token ();
    Token (int     token);
    Token (char    token);
    Token (string& token);
    Token (int setType, int setValue);

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

Token :: Token (int setType, int setValue):
    type_  (setType),
    value_ (setValue)
    {}

std::ostream& Token :: operator << (std::ostream& os)
{
    return os << type_ << " " << value_;
}

void SkipSpace (Stream <char>& example);
void Parser    (Stream <char>& example, Stream <Token>& code);

void SkipSpace (Stream <char>& example)
{
    while (example.check () && (example[example.place ()] == ' '  ||
                                example[example.place ()] == '\n' ||
                                example[example.place ()] == '\t'))
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

            int number = KeyWords[value];

            if (number)
            {
                Token tmp (number, 0);

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
