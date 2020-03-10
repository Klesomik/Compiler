#ifndef BoaSyntaxAnalyzer_hpp

#define BoaSyntaxAnalyzer_hpp

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "..//..//Libraries//Stream.hpp"
#include "BoaToken.hpp"

class BoaSyntaxAnalyzer
{
    public:
        BoaSyntaxAnalyzer ();

        void parsing  (Stream <BoaToken>& from, std::vector <int>& to);

    private:
        std::map <int, int> label_;

        void cmd_push   (Stream <BoaToken>& from, std::vector <int>& to);
        void cmd_pop    (Stream <BoaToken>& from, std::vector <int>& to);
        void cmd_label  (Stream <BoaToken>& from, std::vector <int>& to);
        void cmd_jmp    (Stream <BoaToken>& from, std::vector <int>& to);
        void cmd_in_out (Stream <BoaToken>& from, std::vector <int>& to);
        void cmd_mov    (Stream <BoaToken>& from, std::vector <int>& to);
};

BoaSyntaxAnalyzer::BoaSyntaxAnalyzer ():
    label_ ()
{
}

void BoaSyntaxAnalyzer::parsing (Stream <BoaToken>& from, std::vector <int>& to)
{
    while (from.check ())
    {
        if (from.current ().type != BoaLabel)
            to.push_back (from.current ().type);

        #define BOA(id, params, name, word, comp, cpu) case id: { from++; comp break; }

        switch (from.current ().type)
        {
            #include "BoaList.inl"

            default: { break; }
        }

        #undef BOA
    }
}

void BoaSyntaxAnalyzer::cmd_push (Stream <BoaToken>& from, std::vector <int>& to)
{
    to.push_back (from.current ().type);

    switch (from.current ().type)
    {
        case BoaDigit: {         to.push_back (from.current ().value); break; }
        case   BoaReg: {         to.push_back (from.current ().value); break; }

        case  BoaCell: { from++; to.push_back (from.current ().value); break; }
        case BoaParam: { from++; to.push_back (from.current ().value); break; }

        default: { break; }
    }

    from++;
}

void BoaSyntaxAnalyzer::cmd_pop (Stream <BoaToken>& from, std::vector <int>& to)
{
    switch (from.current ().type)
    {
        case   BoaReg:
        {
            to.push_back (from.current ().type);
            to.push_back (from.current ().value);

            from++;

            break;
        }

        case  BoaCell:
        {
            to.push_back (from.current ().type);
            from++;

            to.push_back (from.current ().value);
            from++;

            break;
        }

        default:
        {
            to.push_back (BoaNone);
            to.push_back (BoaNone);

            break;
        }
    }
}

void BoaSyntaxAnalyzer::cmd_label (Stream <BoaToken>& from, std::vector <int>& to)
{
    label_[from.current ().value] = to.size ();

    from++;
}

void BoaSyntaxAnalyzer::cmd_jmp (Stream <BoaToken>& from, std::vector <int>& to)
{
    std::map <int, int>::iterator it = label_.find (from.current ().value);

    if (it == label_.end ());
        label_[from.current ().value] = -1;

    to.push_back (from.current ().value);

    from++;
}

void BoaSyntaxAnalyzer::cmd_in_out (Stream <BoaToken>& from, std::vector <int>& to)
{
    to.push_back (from.current ().type);

    switch (from.current ().type)
    {
        case  BoaReg: {         to.push_back (from.current ().value); break; }
        case BoaCell: { from++; to.push_back (from.current ().value); break; }

        default: { break; }
    }

    from++;
}

void BoaSyntaxAnalyzer::cmd_mov (Stream <BoaToken>& from, std::vector <int>& to)
{
    to.push_back (from.current ().value);

    from++;
    from++;

    to.push_back (from.current ().value);

    from++;
}

#endif /* BoaSyntaxAnalyzer_hpp */
