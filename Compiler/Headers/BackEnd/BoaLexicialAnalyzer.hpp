//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Stream.hpp"
#include "BoaToken.hpp"

//}==============================================================================

//{==============================================================================

bool search (std::map <std::string, int>& example, std::string& value, const int type, Stream <BoaToken>& code);

//}==============================================================================

bool search (std::map <std::string, int>& example, std::string& value, const int type, Stream <BoaToken>& code)
{
    std::map <std::string, int>::iterator it = example.find (value);

    if (it != example.end ())
    {
        int token = 0;

        if (type == -1) token = it -> second;
        else            token = type;

        code.push_back ({ token, it -> second });

        return true;
    }

    return false;
}

//{==============================================================================

class BoaLexicialAnalyzer
{
    private:
        #define BOA_1(id, params, name, word, comp, cpu)
        #define BOA_2(id, params, name, word, comp, cpu) { word, id },
        #define BOA_3(id, params, name, word, comp, cpu) { word, id },
        #define BOA_4(id, params, name, word, comp, cpu) { word, id },

        std::map <std::string, int> commands_ = {
                                                     #include "BoaList.hpp"
                                                };

        #undef BOA_1
        #undef BOA_2
        #undef BOA_3
        #undef BOA_4

        std::map <std::string, int> regists_ = { { "ax",  0 },
                                                 { "bx",  1 },
                                                 { "bp",  2 },
                                                 { "sp",  3 } };

        std::map <std::string, int> names_;

        Stream <char> buff_;

    public:
        BoaLexicialAnalyzer ();

        void read   (FILE* data);
        void parser (Stream <BoaToken>& code_);

        bool is_space  (const char symbol);
        bool is_digit  (const char symbol);
        bool is_alpha  (const char symbol);
        bool is_symbol (const char symbol);

        void skip   ();
        void number (Stream <BoaToken>& code_);
        void word   (Stream <BoaToken>& code_);
        void sign   (Stream <BoaToken>& code_);
};

//}==============================================================================

BoaLexicialAnalyzer :: BoaLexicialAnalyzer ():
    names_ ({}),
    buff_  ()
    {}

void BoaLexicialAnalyzer :: read (FILE* data)
{
    for (char symbol = 0; fscanf (data, "%c", &symbol) != EOF;)
        buff_.push_back (symbol);
}

void BoaLexicialAnalyzer :: parser (Stream <BoaToken>& code_)
{
    while (buff_.check ())
    {
        if (is_space (buff_[buff_.place ()]))
            skip ();

        else if (is_digit (buff_[buff_.place ()]))
            number (code_);

        else if (is_alpha (buff_[buff_.place ()]))
            word (code_);

        else if (is_symbol (buff_[buff_.place ()]))
            sign (code_);

        else
        {
            std::cout << "|" << buff_[buff_.place ()] << "|\n\n";

            buff_.dump ();

            throw "Unknown symbol";
        }
    }
}

bool BoaLexicialAnalyzer :: is_space (const char symbol)
{
    return (iscntrl (symbol) || (symbol == ' '));
}

bool BoaLexicialAnalyzer :: is_digit (const char symbol)
{
    return isdigit (symbol);
}

bool BoaLexicialAnalyzer :: is_alpha (const char symbol)
{
    return isalpha (symbol);
}

bool BoaLexicialAnalyzer :: is_symbol (const char symbol)
{
    return symbol == '%' ||
           symbol == '$' ||
           symbol == ',';
}

void BoaLexicialAnalyzer :: skip ()
{
    while (buff_.check () && is_space (buff_[buff_.place ()]))
    {
        char digit = 0;
        buff_ >> digit;
    }
}

void BoaLexicialAnalyzer :: number (Stream <BoaToken>& code_)
{
    int value = 0;
    while (buff_.check () && is_digit (buff_[buff_.place ()]))
    {
        char digit = 0;
        buff_ >> digit;

        value = value * 10 + digit - '0';
    }

    code_.push_back ({ BoaDigit, value });
}

void BoaLexicialAnalyzer :: word (Stream <BoaToken>& code_)
{
    std::string value;
    while (buff_.check () && (is_alpha (buff_[buff_.place ()]) || buff_[buff_.place ()] == '_'))
    {
        char symbol = 0;
        buff_ >> symbol;

        value.push_back (symbol);
    }

    if      (search (commands_, value,   -1, code_));
    else if (search ( regists_, value,  BoaReg, code_));
    else if (search (   names_, value, BoaName, code_));

    else
    {
        code_.push_back ({ BoaName, names_.size () });

        names_[value] = names_.size () - 1;
    }
}

void BoaLexicialAnalyzer :: sign (Stream <BoaToken>& code_)
{
    char digit = 0;
    buff_ >> digit;

    std::string value;
    value.push_back (digit);

    int hash_value = commands_[value];

    if (hash_value) code_.push_back ({ hash_value, 0 });
}
