#ifndef CPU_HPP_INCLUDED
    #define CPU_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cassert>
#include <vector>
#include <stack>
#include "BackEnd//BoaToken.hpp"

//}==============================================================================

//TODO: std::vector -> std::stack

//Helper function for stack
//{==============================================================================

template <typename Data_T>
inline void swap (std::vector <Data_T>& example)
{
    Data_T x = example.pop_back ();
    Data_T y = example.pop_back ();

    example.push_back (x);
    example.push_back (y);
}

template <typename Data_T>
inline void dup (std::vector <Data_T>& example) { example.push_back (example.back ()); }

template <typename Data_T>
inline void add (std::vector <Data_T>& example) { example.push_back (example.pop_back () + example.pop_back ()); }

template <typename Data_T>
inline void sub (std::vector <Data_T>& example) { example.push_back (example.pop_back () - example.pop_back ()); }

template <typename Data_T>
inline void mul (std::vector <Data_T>& example) { example.push_back (example.pop_back () * example.pop_back ()); }

template <typename Data_T>
inline void div (std::vector <Data_T>& example) { example.push_back (example.pop_back () / example.pop_back ()); }

template <typename Data_T>
inline void mod (std::vector <Data_T>& example) { example.push_back (example.pop_back () % example.pop_back ()); }

//}==============================================================================

//Struct: Flag
//{==============================================================================

struct Flag
{
    bool mf_, //more
         ef_, //equal
         lf_; //less

    Flag ();

    void reset ();

    void dump ();
};

Flag :: Flag ():
    mf_ (false),
    ef_ (false),
    lf_ (false)
    {}

void Flag :: reset ()
{
    mf_ = false;
    ef_ = false;
    lf_ = false;
}

void Flag :: dump ()
{
    printf ("\n==============================\n");

    printf ("mf_ = %d\n", mf_);
    printf ("ef_ = %d\n", ef_);
    printf ("lf_ = %d\n", lf_);

    printf ("\n==============================\n");
}

//}==============================================================================

//Class: Cpu
//{==============================================================================

class Cpu
{
    private:
        std::vector <int> ram_;
        int regist_[4];
        std::vector <int> data_;

        std::vector <int> code_;

        std::vector <int> call_;

        Flag state_;

        Cpu  (const Cpu& from);

        Cpu& operator = (const Cpu& from);

    public:
        Cpu  ();

        void read (FILE* asmCode);
        void play ();
};

//}==============================================================================

Cpu :: Cpu ():
    ram_    (100),
    regist_ ({}),
    data_   (),
    code_   (),
    call_   (),
    state_  ()
    {}

//===============================================================================

void Cpu :: read (FILE* asmCode)
{
    for (size_t cmd = 0; fscanf (asmCode, "%d", &cmd) != EOF;) code_.push_back (cmd);
}

//===============================================================================

void Cpu :: play ()
{
    for (size_t i = 0; i < code_.size (); i++)
    {
        #define BOA_1(id, params, name, word, comp, cpu)
        #define BOA_2(id, params, name, word, comp, cpu) case id: { cpu break; }
        #define BOA_3(id, params, name, word, comp, cpu) case id: { cpu break; }
        #define BOA_4(id, params, name, word, comp, cpu) case id: { cpu break; }

        switch (code_[i])
        {
            #include "BackEnd//BoaList.hpp"

            default: { return; }
        }

        #undef BOA_1
        #undef BOA_2
        #undef BOA_3
        #undef BOA_4

        //system ("pause");
    }
}

#endif /* CPU_HPP_INCLUDED */
