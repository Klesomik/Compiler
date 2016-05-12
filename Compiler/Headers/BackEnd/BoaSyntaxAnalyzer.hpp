#include <iostream>
#include <cstring>
#include <map>
#include "..//..//Librarys//Vector.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "BoaToken.hpp"

class BoaSyntaxAnalyzer
{
    private:
        Vector <int> code_;

        std::map <int, int> label_;

    public:
        BoaSyntaxAnalyzer ();

        void read  (Stream <BoaToken>& example);
        void write (FILE* bit);

        void cmd_push   (Stream <BoaToken>& example);
        void cmd_pop    (Stream <BoaToken>& example);
        void cmd_label  (Stream <BoaToken>& example);
        void cmd_jmp    (Stream <BoaToken>& example);
        void cmd_in_out (Stream <BoaToken>& example);
        void cmd_mov    (Stream <BoaToken>& example);
};

BoaSyntaxAnalyzer :: BoaSyntaxAnalyzer ():
    code_  (),
    label_ ({})
    {}

void BoaSyntaxAnalyzer :: read (Stream <BoaToken>& example)
{
    while (example.check ())
    {
        if (example[example.place ()].type != BoaLabel)
            code_.push_back (example[example.place ()].type);

        #define BOA_1(id, params, name, word, comp, cpu)
        #define BOA_2(id, params, name, word, comp, cpu) case id: { example++; comp break; }
        #define BOA_3(id, params, name, word, comp, cpu) case id: { example++; comp break; }
        #define BOA_4(id, params, name, word, comp, cpu) case id: { example++; comp break; }

        switch (example[example.place ()].type)
        {
            #include "BoaList.hpp"

            default: { break; }
        }

        #undef BOA_1
        #undef BOA_2
        #undef BOA_3
        #undef BOA_4
    }
}

void BoaSyntaxAnalyzer :: write (FILE* bit)
{
    #define BOA_1(id, params, name, word, comp, cpu)
    #define BOA_2(id, params, name, word, comp, cpu) case id: { for (int j = 0; j < params; j++) { i++; fprintf (bit, "%d ", code_[i]); } break; }
    #define BOA_3(id, params, name, word, comp, cpu)
    #define BOA_4(id, params, name, word, comp, cpu) case id: { i++; fprintf (bit, "%d ", label_[code_[i]]); break; }

    for (size_t i = 0; i < code_.size (); i++)
    {
        fprintf (bit, "%d ", code_[i]);

        switch (code_[i])
        {
            #include "BoaList.hpp"

            default: { break; }
        }
    }

    #undef BOA_1
    #undef BOA_2
    #undef BOA_3
    #undef BOA_4
}

void BoaSyntaxAnalyzer :: cmd_push (Stream <BoaToken>& example)
{
    code_.push_back (example[example.place ()].type);

    switch (example[example.place ()].type)
    {
        case BoaDigit: { code_.push_back (example[example.place ()].value); break; }
        case   BoaReg: { code_.push_back (example[example.place ()].value); break; }

        case  BoaCell: { example++; code_.push_back (example[example.place ()].value); break; }
        case BoaParam: { example++; code_.push_back (example[example.place ()].value); break; }

        default: { break; }
    }

    example++;
}

void BoaSyntaxAnalyzer :: cmd_pop (Stream <BoaToken>& example)
{
    switch (example[example.place ()].type)
    {
        case   BoaReg:
        {
            code_.push_back (example[example.place ()].type);
            code_.push_back (example[example.place ()].value);

            example++;

            break;
        }

        case  BoaCell:
        {
            code_.push_back (example[example.place ()].type);

            example++;

            code_.push_back (example[example.place ()].value);

            example++;

            break;
        }

        default:
        {
            code_.push_back (BoaNone);
            code_.push_back (BoaNone);

            break;
        }
    }
}

void BoaSyntaxAnalyzer :: cmd_label (Stream <BoaToken>& example)
{
    label_[example[example.place ()].value] = code_.size ();

    example++;
}

void BoaSyntaxAnalyzer :: cmd_jmp (Stream <BoaToken>& example)
{
    std::map <int, int>::iterator it = label_.find (example[example.place ()].value);

    if (it != label_.end ());

    else label_[example[example.place ()].value] = -1;

    code_.push_back (example[example.place ()].value);

    example++;
}

void BoaSyntaxAnalyzer :: cmd_in_out (Stream <BoaToken>& example)
{
    code_.push_back (example[example.place ()].type);

    switch (example[example.place ()].type)
    {
        case  BoaReg: { code_.push_back (example[example.place ()].value); break; }
        case BoaCell: { example++; code_.push_back (example[example.place ()].value); break; }

        default: { break; }
    }

    example++;
}

void BoaSyntaxAnalyzer :: cmd_mov (Stream <BoaToken>& example)
{
    code_.push_back (example[example.place ()].value);

    example++;
    example++;

    code_.push_back (example[example.place ()].value);

    example++;
}
