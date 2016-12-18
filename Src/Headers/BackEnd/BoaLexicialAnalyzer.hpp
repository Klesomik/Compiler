//{==============================================================================

#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Libraries//Stream.hpp"
#include "..//..//Libraries//Tools.hpp"
#include "BoaToken.hpp"

//}==============================================================================

//{==============================================================================

class BoaLexicialAnalyzer
{
    public:
        BoaLexicialAnalyzer ();

        void parsing (Stream <char>& from, Stream <BoaToken>& to);

        void skip   (Stream <char>& from);
        void next   (Stream <char>& from);
        void number (Stream <char>& from, Stream <BoaToken>& to);
        void word   (Stream <char>& from, Stream <BoaToken>& to);
        void sign   (Stream <char>& from, Stream <BoaToken>& to);

    private:
        #define BOA(id, params, name, word, comp, cpu) { word, id },

        std::map <std::string, int> commands_ = {
                                                    #include "BoaList.hpp"
                                                };

        #undef BOA

        std::map <std::string, int> regists_ = { { "ax",  0 },
                                                 { "bx",  1 },
                                                 { "bp",  2 },
                                                 { "sp",  3 } };

        std::map <std::string, int> names_;
};

//}==============================================================================

BoaLexicialAnalyzer::BoaLexicialAnalyzer ():
    names_ ()
    {}

void BoaLexicialAnalyzer::parsing (Stream <char>& from, Stream <BoaToken>& to)
{
    while (from.check ())
    {
        if (IsSpace (from.current ()))
            skip (from);

        else if (IsComment (from.current ()))
            next (from);

        else if (IsDigit (from.current ()))
            number (from, to);

        else if (IsAlpha (from.current ()))
            word (from, to);

        else if (IsSymbol (from.current ()))
            sign (from, to);

        else
        {
            std::cout << "|" << from.current () << "|\n\n";

            to.dump ();

            throw "Unknown symbol";
        }
    }
}

void BoaLexicialAnalyzer::skip (Stream <char>& from)
{
    while (from.check () && IsSpace (from.current ()))
    {
        char digit = 0;
        from >> digit;
    }
}

void BoaLexicialAnalyzer::next (Stream <char>& from)
{
    while (from.check () && from.current () != '\n')
    {
        char digit = 0;
        from >> digit;
    }
}

void BoaLexicialAnalyzer::number (Stream <char>& from, Stream <BoaToken>& to)
{
    int value = 0;
    while (from.check () && IsDigit (from.current ()))
    {
        char digit = 0;
        from >> digit;

        value = value * 10 + digit - '0';
    }

    to.push_back ({ BoaDigit, value });
}

void BoaLexicialAnalyzer::word (Stream <char>& from, Stream <BoaToken>& to)
{
    std::string value;
    while (from.check () && (IsAlpha (from.current ()) || from.current () == '_'))
    {
        char symbol = 0;
        from >> symbol;

        value.push_back (symbol);
    }

    if      (Search (commands_, value,      -1, to));
    else if (Search ( regists_, value,  BoaReg, to));
    else if (Search (   names_, value, BoaName, to));

    else
    {
        to.push_back ({ BoaName, names_.size () });

        names_[value] = names_.size () - 1;
    }
}

void BoaLexicialAnalyzer::sign (Stream <char>& from, Stream <BoaToken>& to)
{
    char digit = 0;
    from >> digit;

    std::string value;
    value.push_back (digit);

    int hash_value = commands_[value];

    if (hash_value) to.push_back ({ hash_value, 0 });
}
