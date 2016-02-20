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
    Equal,
    NotEqual,
    And,
    Or,
    LessEqual,
    MoreEqual,
    If,
    Else,
    None,

    OpenBracket  = '(',
    CloseBracket = ')',
    Mul          = '*',
    Div          = '/',
    Mod          = '%',
    Add          = '+',
    Sub          = '-',
    Assignment   = '=',
    Less         = '<',
    More         = '>',
    Begin        = '{',
    End          = '}',
    EndOfToken   = ';'
};

//}==============================================================================

//{==============================================================================

map <string, int> Operators = { {  "{",        Begin },
                                {  "}",          End },
                                {  ";",   EndOfToken },
                                {  "(",  OpenBracket },
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

map <string, int> Variables;

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
    char tmp[9] = "";

    switch (type)
    {
        case     Digit: { sprintf (tmp, "%d",     type); break; }
        case       Var: { sprintf (tmp, "var_%d", type); break; }
        case     Equal: { sprintf (tmp, "==");           break; }
        case  NotEqual: { sprintf (tmp, "!=");           break; }
        case       And: { sprintf (tmp, "&&");           break; }
        case        Or: { sprintf (tmp, "||");           break; }
        case LessEqual: { sprintf (tmp, "<=");           break; }
        case MoreEqual: { sprintf (tmp, ">=");           break; }
        case        If: { sprintf (tmp, "if");           break; }
        case      Else: { sprintf (tmp, "else");         break; }
        case      None: { sprintf (tmp, "none");         break; }
    }

    return os << tmp;
}

void Parser (Stream <char>& example, Stream <Token>& code);

void Parser (Stream <char>& example, Stream <Token>& code)
{
    while (example.check ())
    {
        if (isspace (example[example.place ()])) //iscntrl
        {
            while (example.check () && isspace (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;
            }
        }

        else if (isdigit (example[example.place ()]))
        {
            int value = 0;
            while (example.check () && isdigit (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value = value * 10 + digit - '0';
            }

            code.push_back ({ Digit, value });
        }

        else if (isalpha (example[example.place ()]))
        {
            string value;
            while (example.check () && isalpha (example[example.place ()]))
            {
                char symbol = 0;
                example >> symbol;

                value.push_back (symbol);
            }

            int hash_value = KeyWords[value];

            if (hash_value) code.push_back ({ hash_value, 0 });

            else
            {
                int hash_value = Variables[value];

                if (hash_value) code.push_back ({ Var, hash_value });

                else
                {
                    Variables.insert (pair <string, int> (value, Variables.size ()));

                    code.push_back ({ Var, Variables.size () });
                }
            }
        }

        else if (ispunct (example[example.place ()]))
        {
            string value;
            while (example.check () && ispunct (example[example.place ()]))
            {
                char digit = 0;
                example >> digit;

                value.push_back (digit);
            }

            int hash_value = Operators[value];

            if (hash_value) code.push_back ({ hash_value, 0 });
        }

        else
        {
            cout << example[example.place ()] << "\n\n";

            THROW ("Unknown symbol");
        }
    }
}
