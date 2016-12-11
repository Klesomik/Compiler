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

        std::vector <int> call_;

        Flag state_;

        Cpu  (const Cpu& from);

        Cpu& operator = (const Cpu& from);

    public:
        Cpu  (const size_t ram_size);

        void play ();
};

//}==============================================================================

Cpu::Cpu (const size_t ram_size):
    ram_    (ram_size),
    regist_ ({}),
    data_   (),
    call_   (),
    state_  ()
    {}

//===============================================================================

void Cpu::parsing (const std::vector <int>& code_)
{
    for (size_t i = 0; i < code_.size (); i++)
    {
        #define BOA(id, params, name, word, comp, cpu) case id: { cpu break; }

        switch (code_[i])
        {
            #include "BackEnd//BoaList.inl"

            default: { return; }
        }

        #undef BOA
    }
}

#endif /* CPU_HPP_INCLUDED */
