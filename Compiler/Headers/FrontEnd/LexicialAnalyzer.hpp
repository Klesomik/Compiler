//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"
#include "Token.hpp"

//}==============================================================================

//{==============================================================================

class LexicialAnalyzer
{
    private:
        #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code)
        #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) { word, id },
        #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code)

        std::map <std::string, int> commands_ = {
                                                    #include "CList.hpp"
                                                };

        #undef DEER_0
        #undef DEER_1
        #undef DEER_2

        #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code)
        #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code)
        #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) { word, id },

        std::map <std::string, int> preProc_ = {
                                                   #include "CList.hpp"
                                               };

        #undef DEER_0
        #undef DEER_1
        #undef DEER_2

        std::map <std::string, int> names_;

        size_t line_;

    public:
        LexicialAnalyzer (FILE* c_file, Stream <Token>& code);

        bool search (std::map <std::string, int>& example, std::string& value, const int type, Stream <Token>& code);

        bool IsSpace   (const char symbol);
        bool IsComment (const char symbol);
        bool IsPreProc (const char symbol);
        bool IsDigit   (const char symbol);
        bool IsAlpha   (const char symbol);
        bool IsUnary   (const char symbol);
        bool IsBinary  (const char symbol);

        void Skip           (Stream <char>& example);
        void Comment        (Stream <char>& example);
        void PreProc        (Stream <char>& example, Stream <Token>& code);
        void Number         (Stream <char>& example, Stream <Token>& code);
        void Word           (Stream <char>& example, Stream <Token>& code);
        void OperatorUnary  (Stream <char>& example, Stream <Token>& code);
        void OperatorBinary (Stream <char>& example, Stream <Token>& code);
        void Parser         (Stream <char>& example, Stream <Token>& code);
};

//}==============================================================================

LexicialAnalyzer :: LexicialAnalyzer (FILE* c_file, Stream <Token>& code):
    names_ ({ { "main", 0 } }),
    line_  (0)
    {
        Stream <char> example;

        for (char symbol = 0; fscanf (c_file, "%c", &symbol) != EOF;)
            example.push_back (symbol);

        Parser (example, code);
    }

//===============================================================================

bool LexicialAnalyzer :: search (std::map <std::string, int>& example, std::string& value, const int type, Stream <Token>& code)
{
    std::map <std::string, int>::iterator it = example.find (value);

    if (it != example.end ())
    {
        int token = 0;

        if (type == -1) token = it -> second;
        else            token = type;

        code.push_back ({ token, it -> second, line_ });

        return true;
    }

    return false;
}

//===============================================================================

bool LexicialAnalyzer :: IsSpace (const char symbol)
{
    if (iscntrl (symbol) || (symbol == ' '))
    {
        if (symbol == '\n') line_++;

        return true;
    }

    return false;
}

//===============================================================================

bool LexicialAnalyzer :: IsComment (const char symbol)
{
    return symbol == '/';
}

//===============================================================================

bool LexicialAnalyzer :: IsPreProc (const char symbol)
{
    return symbol == '#';
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

bool LexicialAnalyzer :: IsUnary (const char symbol)
{
    return symbol == ',' ||
           symbol == '(' ||
           symbol == ')' ||
           symbol == '{' ||
           symbol == '}' ||
           symbol == ';';
}

//===============================================================================

bool LexicialAnalyzer :: IsBinary (const char symbol)
{
    return symbol == '=' ||
           symbol == '!' ||
           symbol == '&' ||
           symbol == '|' ||
           symbol == '<' ||
           symbol == '>' ||
           symbol == '-' ||
           symbol == '+' ||
           symbol == '*' ||
           symbol == '/' ||
           symbol == '%';
}

//===============================================================================

void LexicialAnalyzer :: Skip (Stream <char>& example)
{
    while (example.check () && IsSpace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

//===============================================================================

void LexicialAnalyzer :: Comment (Stream <char>& example)
{
    std::string name;

    while (example.check () && IsComment (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        name.push_back (symbol);
    }

    if (name == "//")
    {
        while (example.check () && example[example.place ()] != '\n')
        {
            char skip = 0;
            example >> skip;
        }
    }

    if (name == "/*")
    {
    }
}

//===============================================================================

void LexicialAnalyzer :: PreProc (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (example.check () && IsAlpha (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    std::map <std::string, int>::iterator it = preProc_.find (value);

    if (it != preProc_.end ())
    {
    }

    else throw "Unknown symbol";
}

//===============================================================================

void LexicialAnalyzer :: Number (Stream <char>& example, Stream <Token>& code)
{
    int value = 0;
    while (example.check () && IsDigit (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;

        value = value * 10 + digit - '0';
    }

    code.push_back ({ Digit, value, line_ });
}

//===============================================================================

void LexicialAnalyzer :: Word (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (example.check () && IsAlpha (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    if      (search (commands_, value,   -1, code));
    else if (search (   names_, value, Name, code));

    else
    {
        code.push_back ({ Name, names_.size (), line_ });

        names_[value] = names_.size () - 1;
    }
}

//===============================================================================

void LexicialAnalyzer :: OperatorUnary (Stream <char>& example, Stream <Token>& code)
{
    char digit = 0;
    example >> digit;

    std::string value;
    value.push_back (digit);

    int hash_value = commands_[value];

    if (hash_value) code.push_back ({ hash_value, 0, line_ });
}

//===============================================================================

void LexicialAnalyzer :: OperatorBinary (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (example.check () && IsBinary (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;

        value.push_back (digit);
    }

    int hash_value = commands_[value];

    if (hash_value) code.push_back ({ hash_value, 0, line_ });
}

//===============================================================================

void LexicialAnalyzer :: Parser (Stream <char>& example, Stream <Token>& code)
{
    while (example.check ())
    {
        if (IsSpace (example[example.place ()]))
            Skip (example);

        else if (example.check_next ({ '/', '/' }) || example.check_next ({ '/', '*' }))
            Comment (example);

        else if (IsDigit (example[example.place ()]))
            Number (example, code);

        else if (IsAlpha (example[example.place ()]))
            Word (example, code);

        else if (IsUnary (example[example.place ()]))
            OperatorUnary (example, code);

        else if (IsBinary (example[example.place ()]))
            OperatorBinary (example, code);

        else
        {
            std::cout << example[example.place ()] << "\n\n";

            throw "Unknown symbol";
        }
    }
}
