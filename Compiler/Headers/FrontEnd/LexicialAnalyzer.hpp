#pragma once

//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"
#include "Token.hpp"

//}==============================================================================

using namespace std;

class LexicialAnalyzer
{
    private:
        map <string, int> operators_ = { {  "{",        Begin },
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

        map <string, int> keyWords_ = { {   "if",     If },
                                        {  "else",  Else },
                                        { "while", While },
                                        {   "int",   Int } };

        map <string, int> preProc_ = { { "#include", Include },
                                      {  "#define",  Define } };

        map <string, int> names_;

    public:
        LexicialAnalyzer (Stream <Token>& code);

        void Skip     (Stream <char>& example);
        void Number   (Stream <char>& example, Stream <Token>& code);
        void Word     (Stream <char>& example, Stream <Token>& code);
        void Operator (Stream <char>& example, Stream <Token>& code);
        void Parser   (Stream <char>& example, Stream <Token>& code);
};

LexicialAnalyzer :: LexicialAnalyzer (Stream <Token>& code):
    names_ ({})
    {
        Stream <char> example;

        for (char symbol = 0; fscanf (Inform.c_file, "%c", &symbol) != EOF;)
            example.push_back (symbol);

        Parser (example, code);
    }

void LexicialAnalyzer :: Skip (Stream <char>& example)
{
    while (example.check () && isspace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

void LexicialAnalyzer :: Number (Stream <char>& example, Stream <Token>& code)
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

void LexicialAnalyzer :: Word (Stream <char>& example, Stream <Token>& code)
{
    string value;
    while (example.check () && isalpha (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    int hash_value = keyWords_[value];

    if (hash_value) code.push_back ({ hash_value, 0 });

    else
    {
        hash_value = names_[value];

        if (hash_value) code.push_back ({ Var, hash_value });

        else
        {
            code.push_back ({ Var, names_.size () + 1 });

            names_[value] = names_.size () + 1;
        }
    }
}

void LexicialAnalyzer :: Operator (Stream <char>& example, Stream <Token>& code)
{
    string value;
    while (example.check () && ispunct (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;

        value.push_back (digit);
    }

    int hash_value = operators_[value];

    if (hash_value) code.push_back ({ hash_value, 0 });
}

void LexicialAnalyzer :: Parser (Stream <char>& example, Stream <Token>& code)
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
