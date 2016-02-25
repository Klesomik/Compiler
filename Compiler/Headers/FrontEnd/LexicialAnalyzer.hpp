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
    While,
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

map <string, int> KeyWords = { {   "if",     If },
                               {  "else",  Else },
                               { "while", While } };

map <string, int> Variables = {};

map <string, int> Functions;

//}==============================================================================

//{==============================================================================

struct Token
{
    int  type;

    union
    {
        int value;
    };

    Token ();
    Token (int setType, int setValue);

    //std::ostream& operator << (std::ostream& os);
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

std::ostream& operator << (std::ostream& os, Token const &m);

std::ostream& operator << (std::ostream& os, Token const &m)
{
    char tmp[9] = "";

    switch (m.type)
    {
        case     Digit: { sprintf (tmp, "%d",     m.value); break; }

        case       Var: { sprintf (tmp, "var_%d", m.value); break; }
        case     Equal: { sprintf (tmp, "==");              break; }
        case  NotEqual: { sprintf (tmp, "!=");              break; }
        case       And: { sprintf (tmp, "&&");              break; }
        case        Or: { sprintf (tmp, "||");              break; }
        case LessEqual: { sprintf (tmp, "<=");              break; }
        case MoreEqual: { sprintf (tmp, ">=");              break; }
        case        If: { sprintf (tmp, "if");              break; }
        case      Else: { sprintf (tmp, "else");            break; }
        case     While: { sprintf (tmp, "while");           break; }
        case      None: { sprintf (tmp, "none");            break; }

        default:        { sprintf (tmp, "%c", m.type);      break; }
    }

    return os << tmp;
}

//{==============================================================================

void Skip     (Stream <char>& example);
void Number   (Stream <char>& example, Stream <Token>& code);
void Word     (Stream <char>& example, Stream <Token>& code);
void Operator (Stream <char>& example, Stream <Token>& code);
void Parser   (Stream <char>& example, Stream <Token>& code);

//}==============================================================================

void Skip (Stream <char>& example)
{
    while (example.check () && isspace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

void Number (Stream <char>& example, Stream <Token>& code)
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

void Word (Stream <char>& example, Stream <Token>& code)
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
        hash_value = Variables[value];

        if (hash_value) code.push_back ({ Var, hash_value });

        else
        {
            code.push_back ({ Var, Variables.size () + 1 });

            Variables[value] = Variables.size () + 1;
        }
    }
}

void Operator (Stream <char>& example, Stream <Token>& code)
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

void Parser (Stream <char>& example, Stream <Token>& code)
{
    while (example.check ())
    {
        if (isspace (example[example.place ()])) //iscntrl
            Skip (example);

        else if (isdigit (example[example.place ()]))
            Number (example, code);

        else if (isalpha (example[example.place ()]))
            Word (example, code);

        else if (ispunct (example[example.place ()]))
            Operator (example, code);

        else
        {
            cout << example[example.place ()] << "\n\n";

            THROW ("Unknown symbol");
        }
    }
}
