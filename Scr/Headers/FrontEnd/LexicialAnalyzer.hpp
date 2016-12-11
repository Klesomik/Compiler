#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Libraries//Stream.hpp"
#include "..//..//Libraries//Tools.hpp"
#include "Token.hpp"

class LexicialAnalyzer
{
    public:
        LexicialAnalyzer ();

        bool IsUnary     (const char symbol);
        bool IsBinary    (const char symbol);

        void Skip           (Stream <char>& example);
        void Comment        (Stream <char>& example);
        void PreProc        (Stream <char>& example, Stream <Token>& code);
        void Number         (Stream <char>& example, Stream <Token>& code);
        void Word           (Stream <char>& example, Stream <Token>& code);
        void OperatorUnary  (Stream <char>& example, Stream <Token>& code);
        void OperatorBinary (Stream <char>& example, Stream <Token>& code);
        void Parser         (Stream <char>& example, Stream <Token>& code);

    private:
        #define DEER(id, name, word, code) { word, id },

        std::map <std::string, int> commands_ = {
                                                    #include "CList.hpp"
                                                };

        #undef DEER

        std::set <std::string> comments_  = { "//", "/*" };

        std::set <std::string> operators_ = { ",",
                                              "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=",
                                              "||",
                                              "&&",
                                              "|",
                                              "^",
                                              "&",
                                              "==", "!=",
                                              "<", ">", "<=", ">=",
                                              "<<", ">>",
                                              "+", "-",
                                              "*", "/", "%",
                                              "++", "--", "!", "~"  };

        std::map <std::string, int> names_;
};

LexicialAnalyzer :: LexicialAnalyzer ():
    names_ ({ { "main", 0 } })
{
}

void LexicialAnalyzer::parsing (Stream <char>& from, Stream <Token>& to)
{
    while (from.check ())
    {
        if (IsSpace (from.current ()))
            Skip (from);

        else if (comments_.find (from))
            Comment (from);

        else if (IsPreProc (from.current ()))
            PreProc (from, code);

        else if (IsDigit (from.current ()))
            Number (from, code);

        else if (IsAlpha (from.current ()))
            Word (from, code);

        else if (IsUnary (from.current ()))
            OperatorUnary (from, code);

        else if (IsBinary (from.current ()))
            OperatorBinary (from, code);

        else
        {
            std::cout << from.current () << "\n\n";

            throw "Unknown symbol";
        }
    }
}

bool LexicialAnalyzer :: IsUnary (const char symbol)
{
    return symbol == ',' ||
           symbol == '(' ||
           symbol == ')' ||
           symbol == '{' ||
           symbol == '}' ||
           symbol == ';';
}

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

void LexicialAnalyzer :: Skip (Stream <char>& example)
{
    while (example.check () && IsSpace (example[example.place ()]))
    {
        char digit = 0;
        example >> digit;
    }
}

void LexicialAnalyzer :: Comment (Stream <char>& example)
{
    std::string name;

    while (example.check () && example[example.place ()] == '/')
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

void LexicialAnalyzer :: PreProc (Stream <char>& example, Stream <Token>& code)
{
    std::string value;
    while (example.check () && IsAlpha (example[example.place ()]))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    code.push_back ({ preProc_[value], 0, 0 });

    if (example.check () && IsQuotation (example[example.place ()]))
    {
        char start = 0;
        std::cin >> start;
    }

    Word (example, code);

    if (example.check () && IsQuotation (example[example.place ()]))
    {
        char start = 0;
        std::cin >> start;
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
        code.push_back ({ Name, names_.size () });

        names_[value] = names_.size () - 1;
    }
}

void LexicialAnalyzer :: OperatorUnary (Stream <char>& example, Stream <Token>& code)
{
    char digit = 0;
    example >> digit;

    std::string value;
    value.push_back (digit);

    int hash_value = commands_[value];

    if (hash_value) code.push_back ({ hash_value, 0 });
}

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

    if (hash_value) code.push_back ({ hash_value, 0 });
}
