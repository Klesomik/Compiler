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
        #define DEER(id, name, word) { word, id }

        map <string, int> commands_ = {
                                          #include "CList.hpp"
                                      }

        #undef DEER(id, name, word)

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

bool LexicialAnalyzer :: IsSpace (const char symbol)
{
    return (iscntrl (symbol) || ' ');
}

bool LexicialAnalyzer :: IsDigit (const char symbol)
{
    return isdigit (symbol);
}

bool LexicialAnalyzer :: IsAlpha (const char symbol)
{
    return isalpha (symbol);
}

bool LexicialAnalyzer :: IsPunct (const char symbol)
{
    return ispunct (symbol);
}

void LexicialAnalyzer :: Skip (Stream <char>& example)
{
    while (example.check () && IsSpace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

void LexicialAnalyzer :: Number (Stream <char>& example, Stream <Token>& code)
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

void LexicialAnalyzer :: Word (Stream <char>& example, Stream <Token>& code)
{
    string value;
    while (example.check () && isalpha (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    int hash_value = commands_[value];

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
        if (isspace (example[example.place ()]))
            Skip (example);

        else if (isdigit (example[example.place ()]))
            Number (example, code);

        else if (IsAlpha (example[example.place ()]))
            Word (example, code);

        else if (IsPunct (example[example.place ()]))
            Operator (example, code);

        else
        {
            cout << example[example.place ()] << "\n\n";

            THROW ("Unknown symbol");
        }
    }
}
