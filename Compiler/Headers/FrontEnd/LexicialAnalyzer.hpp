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
    Less,
    LessEqual,
    More,
    MoreEqual,

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

map <char, int> SpecialSymbols = { { '{',      Begin },
                                   { '}',        End },
                                   { ';', EndOfToken }, };

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
                                {  "=",   Assignment },
                                {  "<",         Less },
                                { "<=",    LessEqual },
                                {  ">",         More },
                                { ">=",    MoreEqual } };

map <string, int> KeyWords = { {   "if",   If },
                               { "else", Else } };

Vector <string> Names;
//map <string, int> Names = {};

//}==============================================================================

//{==============================================================================

//union
//{
//};

struct Token
{
    int  type;
    int value;

    Token ();
    Token (int setType, int setValue);

    std::ostream& operator << (std::ostream& os);
};

//}==============================================================================

Token :: Token ():
    type  (),
    value ()
    {}

Token :: Token (int setType, int setValue):
    type  (setType),
    value (setValue)
    {}

std::ostream& Token :: operator << (std::ostream& os)
{
    return os << type << " " << value;
}

bool IsOther         (char c);
bool IsDigit         (char c);
bool IsLetter        (char c);
bool IsOperator      (char c);
bool IsSpecialSymbol (char c);
void Parser    (Stream <char>& example, Stream <Token>& code);

bool IsOther (char c)
{
    return c == ' '  ||
           c == '\n' ||
           c == '\t' ||
           c == '\b';
}

bool IsDigit (char c)
{
	return c >= '0' && c <= '9';
}

bool IsLetter (char c)
{
	return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c == '_')             ||
           (c == '$');
}

bool IsOperator (char c)
{
    return c == '(' ||
           c == ')' ||
           c == '*' ||
           c == '/' ||
           c == '%' ||
           c == '+' ||
           c == '-' ||
           c == '=' ||
           c == '!' ||
           c == '&' ||
           c == '|' ||
           c == '<' ||
           c == '>';
}

bool IsSpecialSymbol (char c)
{
    return c == '{' ||
           c == '}' ||
           c == ';';
}

void Parser (Stream <char>& example, Stream <Token>& code)
{
    while (example.check ())
    {
        if (IsOther (example[example.place ()]))
        {
            while (example.check () && IsOther (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;
            }
        }

        else if (IsDigit (example[example.place ()]))
        {
            int value = 0;
            while (example.check () && IsDigit (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value = value * 10 + digit - '0';
            }

            code.push_back ({ Digit, value });
        }

        else if (IsLetter (example[example.place ()]))
        {
            string value;
            while (example.check () && IsLetter (example[example.place ()]))
            {
                char symbol = 0;
                example >> symbol;

                value.push_back (symbol);
            }

            int hash_value = KeyWords[value];

            if (hash_value) code.push_back ({ hash_value, 0 });

            else
            {
                bool first = false;
                for (size_t i = 0; i < Names.size (); i++)
                {
                    if (Names[i] == value)
                    {
                        code.push_back ({ Var, i });

                        first = true;
                    }
                }

                if (!first)
                {
                    Names.push_back (value);

                    code.push_back ({ Var, Names.size () - 1 });
                }
            }
        }

        else if (IsOperator (example[example.place ()]))
        {
            string value;
            while (example.check () && IsOperator (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value.push_back (digit);
            }

            int hash_value = Operators[value];

            if (hash_value) code.push_back ({ hash_value, 0 });
        }

        else if (IsSpecialSymbol (example[example.place ()]))
        {
            char symbol = 0;
            example >> symbol;

            code.push_back ({ SpecialSymbols[symbol], 0 });
        }

        else throw "Unknown symbol";
    }
}
