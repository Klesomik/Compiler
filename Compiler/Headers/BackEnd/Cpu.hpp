#ifndef CPU_HPP_INCLUDED
    #define CPU_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cassert>
#include "..//..//Librarys//Vector.hpp"
#include "..//..//Librarys//Stack.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define TEST_CPU

#ifdef DEBUG_CPU

    #define OK_CPU assert (ok ());

#endif /* DEBUG_CPU */

#ifdef TEST_CPU

    #define OK_CPU ok ();

#endif /* TEST_CPU */

#ifdef RELASE_CPU

    #define OK_CPU

#endif /* RELASE_CPU */

//}==============================================================================

//Namespace
//{==============================================================================

using namespace CpuCompiler;

//}==============================================================================

//Helper function for stack
//{==============================================================================

template <typename Data_T>
inline void swap (Stack <Data_T>& example)
{
    Data_T x = example.pop ();
    Data_T y = example.pop ();

    example.push (x);
    example.push (y);
}

template <typename Data_T>
inline void dup (Stack <Data_T>& example) { example.push (example.top ()); }

template <typename Data_T>
inline void add (Stack <Data_T>& example) { example.push (example.pop () + example.pop ()); }

template <typename Data_T>
inline void sub (Stack <Data_T>& example) { example.push (example.pop () - example.pop ()); }

template <typename Data_T>
inline void mul (Stack <Data_T>& example) { example.push (example.pop () * example.pop ()); }

template <typename Data_T>
inline void div (Stack <Data_T>& example) { example.push (example.pop () / example.pop ()); }

template <typename Data_T>
inline void mod (Stack <Data_T>& example) { example.push (example.pop () % example.pop ()); }

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
        Vector <int> ram_;
        int regist_[12];
        Stack <int> data_;

        Vector <int> code_;

        Stack <int> call_;

        Flag state_;

        FILE* asmCode_;

        bool ok   ();
        void dump ();

    public:
        Cpu  ();
        ~Cpu ();
        Cpu  (const Cpu& from);

        Cpu& operator = (const Cpu& from);

        void read ();
        void play ();

        FILE* AsmCode () /*const*/;
};

//}==============================================================================

Cpu :: Cpu ():
    ram_    (100),
    regist_ ({}),
    data_   (),
    code_   (),
    call_   (),
    state_  (),
    asmCode_ (fopen (InIt.Asm.c_str (), "r"))
    { OK_CPU }

//===============================================================================

Cpu :: ~Cpu ()
{
    fclose (asmCode_);

    asmCode_ = nullptr;
}

//===============================================================================

void Cpu :: read ()
{
    OK_CPU

    for (size_t cmd = 0; fscanf (asmCode_, "%d", &cmd) != EOF;) code_.push_back (cmd);

    OK_CPU
}

//===============================================================================

void Cpu :: play ()
{
    OK_CPU

    for (size_t i = 0; i < code_.size (); i++)
    {
        #define CMD(id, name, pre, comp, cpu)\
        case CMD_##name:\
        {\
            cpu\
            break;\
        }

        switch (code_[i])
        {
            #include "..//CommandsList.hpp"

            default: { return; }
        }

        #undef CMD
    }

    OK_CPU
}

//===============================================================================

FILE* Cpu :: AsmCode () /*const*/
{
    OK_CPU

    return asmCode_;
}

//===============================================================================

bool Cpu :: ok ()
{
    if (!asmCode_)
    {
        #ifdef DEBUG_CPU

            return false;

        #endif /* DEBUG_CPU */

        #ifdef TEST_CPU

            throw "!asmCode_";

        #endif /* TEST_CPU */

        #ifdef RELASE_CPU

        #endif /* RELASE_CPU */
    }

    return true;
}

//===============================================================================

void Cpu :: dump ()
{
}

#endif /* CPU_HPP_INCLUDED */
