#pragma once

//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"
#include "..//DeerLib.hpp"
#include "..//Token.hpp"

//}==============================================================================

//{==============================================================================

class LexicialAnalyzer
{
    private:
        #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style) { word, id },

        std::map <std::string, int> commands_ = {
                                                    #include "..//CList.hpp"
                                                };

        #undef DEER

        std::map <std::string, int> names_;

    public:
        LexicialAnalyzer (Stream <Token>& code);

        bool IsSpace (const char symbol);
        bool IsDigit (const char symbol);
        bool IsAlpha (const char symbol);
        bool IsPunct (const char symbol);

        void Skip     (Stream <char>& example);
        void Number   (Stream <char>& example, Stream <Token>& code);
        void Word     (Stream <char>& example, Stream <Token>& code);
        void Operator (Stream <char>& example, Stream <Token>& code);
        void Parser   (Stream <char>& example, Stream <Token>& code);

        void Hello_C (std::string& example);
};

//}==============================================================================

LexicialAnalyzer :: LexicialAnalyzer (Stream <Token>& code):
    names_ ({})
    {
        std::string name;
        Hello_C (name);

        FILE* c_file = fopen (name.c_str (), "r");

        Stream <char> example;

        for (char symbol = 0; fscanf (c_file, "%c", &symbol) != EOF;)
            example.push_back (symbol);

        fclose (c_file);
                c_file = nullptr;

        Parser (example, code);
    }

//===============================================================================

void LexicialAnalyzer :: Hello_C (std::string& example)
{
    printf ("Input name of C file: ");

    getline (std::cin, example, '\n');
}

//===============================================================================

bool LexicialAnalyzer :: IsSpace (const char symbol)
{
    return (iscntrl (symbol) || (symbol == ' '));
}

//===============================================================================

bool LexicialAnalyzer :: IsDigit (const char symbol)
{
    return isdigit (symbol);
}

//===============================================================================

bool LexicialAnalyzer :: IsAlpha (const char symbol)
{
    return isalpha (symbol);
}

//===============================================================================

bool LexicialAnalyzer :: IsPunct (const char symbol)
{
    return ispunct (symbol);
}

//===============================================================================

void LexicialAnalyzer :: Skip (Stream <char>& example)
{
    while (check (example) && IsSpace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

//===============================================================================

void LexicialAnalyzer :: Number (Stream <char>& example, Stream <Token>& code)
{
    int value = 0;
    while (check (example) && IsDigit (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;

        value = value * 10 + digit - '0';
    }

    code.push_back ({ Digit, value });
}

//===============================================================================

void LexicialAnalyzer :: Word (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (check (example) && isalpha (example[example.place ()]))
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

//===============================================================================

void LexicialAnalyzer :: Operator (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (check (example) && ispunct (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;

        value.push_back (digit);
    }

    int hash_value = commands_[value];

    if (hash_value) code.push_back ({ hash_value, 0 });
}

//===============================================================================

void LexicialAnalyzer :: Parser (Stream <char>& example, Stream <Token>& code)
{
    while (check (example))
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
            std::cout << example[example.place ()] << "\n\n";

            THROW ("Unknown symbol");
        }
    }
}
