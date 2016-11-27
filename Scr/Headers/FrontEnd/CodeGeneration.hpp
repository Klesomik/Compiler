#ifndef CodeGeneration_hpp
    #define CodeGeneration_hpp

//{==============================================================================

#include <cstdio>
#include <iostream>

//}==============================================================================

#define FPRINTF writeIndent (write); fprintf

#define BLOCK(comment, code)\
FPRINTF (write, ";{==========%s\n", comment);\
addIndent (4);\
\
    code \
\
subIndent (4);\
FPRINTF (write, ";}==========%s\n\n", comment);

//{==============================================================================

class CodeGeneration
{
    private:
        size_t jmp_;

        int size_ram_;

        size_t count_;

        void addIndent   (const int space);
        void subIndent   (const int space);
        void writeIndent (FILE* write);

    public:
        CodeGeneration (AstNode& root, FILE* write, const size_t func);

        void Generate (AstNode& root, FILE* write);

        void CreateAsm                                         (AstNode* current, FILE* write);
        void give_Add_Sub_Mul_Div_Mod                          (AstNode* current, FILE* write, const char* command);
        void give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (AstNode* current, FILE* write, const char* if_comand, const char* else_comand);
        void give_And                                          (AstNode* current, FILE* write);
        void give_Or                                           (AstNode* current, FILE* write);
        void give_Assignment                                   (AstNode* current, FILE* write);
        void give_If                                           (AstNode* current, FILE* write);
        void give_While                                        (AstNode* current, FILE* write);
        void give_Declaration                                  (AstNode* current, FILE* write);
        void give_Digit                                        (AstNode* current, FILE* write);
        void give_Name                                         (AstNode* current, FILE* write);
        void give_Block                                        (AstNode* current, FILE* write);
        void give_DeclFunc                                     (AstNode* current, FILE* write);
        void give_DeclVar                                      (AstNode* current, FILE* write);
        void give_Call                                         (AstNode* current, FILE* write);
        void give_Return                                       (AstNode* current, FILE* write);
        void give_Out                                          (AstNode* current, FILE* write);
};

//}==============================================================================

CodeGeneration :: CodeGeneration (AstNode& root, FILE* write, const size_t func):
    jmp_      (func + 1),
    size_ram_ (0),
    count_    (0)
    {
        Generate (root, write);
    }

//===============================================================================

void CodeGeneration :: Generate (AstNode& root, FILE* write)
{
    const int number_of_main = 0;

    FPRINTF (write, "call %d\n", number_of_main);
    FPRINTF (write, "eof\n\n");

    for (size_t i = 0; i < root.size (); i++)
    {
        size_ram_ = 0;

        CreateAsm (root[i], write);
    }
}

//===============================================================================

void CodeGeneration :: addIndent (const int space)
{
    count_ += space;
}

//===============================================================================

void CodeGeneration :: subIndent (const int space)
{
    count_ -= space;
}

//===============================================================================

void CodeGeneration :: writeIndent (FILE* write)
{
    for (size_t i = 0; i < count_; i++)
        fprintf (write, " ");
}

//===============================================================================

void CodeGeneration :: CreateAsm (AstNode* current, FILE* write)
{
    #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code) case id: { code break; }
    #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) case id: { code break; }
    #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) case id: { code break; }

    switch (current -> key ().type)
    {
        #include "CList.hpp"

        default: { std::cout << current -> key ().type << "\n"; throw "default: error"; }
    }

    #undef DEER_0
    #undef DEER_1
    #undef DEER_2
}

//===============================================================================

void CodeGeneration :: give_Add_Sub_Mul_Div_Mod (AstNode* current, FILE* write, const char* command)
{
    BLOCK ("Actions",
    {
        for (int i = current -> size () - 1; i >= 0; i--)
            CreateAsm (current -> children ()[i], write);

        for (size_t i = 0; i < current -> size () - 1; i++)
            FPRINTF (write, "%s\n", command);
    })
}

//===============================================================================

void CodeGeneration :: give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (AstNode* current, FILE* write, const char* if_comand, const char* else_comand)
{
    for (int i = current -> size () - 1; i >= 0; i--)
        CreateAsm (current -> children ()[i], write);

    FPRINTF (write, "cmp_f\n");

    for (size_t i = 0; i < current -> size (); i++)
        FPRINTF (write, "pop\n");

    size_t copy_1 = jmp_++;
    size_t copy_2 = jmp_;//++
    //size_t copy_3 = jmp_++;

    FPRINTF (write, "%s %d\n",   if_comand, copy_1);
    FPRINTF (write, "%s %d\n", else_comand, copy_2);

    FPRINTF (write, "label %d\n",           copy_1);

    /*FPRINTF (write, "push 1\n");
    FPRINTF (write, "jmp %d\n",             copy_3);

    FPRINTF (write, "label %d\n",           copy_2);

    FPRINTF (write, "push 0\n");

    FPRINTF (write, "label %d\n",           copy_3);*/
}

//===============================================================================

void CodeGeneration :: give_And (AstNode* current, FILE* write)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> size () - 1; i++)
        FPRINTF (write, "mul\n");
}

//===============================================================================

void CodeGeneration :: give_Or (AstNode* current, FILE* write)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> size () - 1; i++)
        FPRINTF (write, "add\n");
}

//===============================================================================

void CodeGeneration :: give_Assignment (AstNode* current, FILE* write)
{
    CreateAsm (current -> children ()[current -> children ().size () - 1], write);

    for (size_t i = 0; i < current -> children ().size () - 1; i++)
    {
        FPRINTF (write, "dup\n");

        FPRINTF (write, "pop %%%d\n", current -> children ()[i] -> key ().value);
    }

    FPRINTF (write, "pop\n");
}

//===============================================================================

void CodeGeneration :: give_If (AstNode* current, FILE* write)
{
    BLOCK ("If",
    {
        switch (current -> children ()[0] -> key ().type)
        {
            case Equal:     { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "je", "jne"); break; }
            case NotEqual:  { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jne",  "je"); break; }
            case Less:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "jl", "jme"); break; }
            case LessEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jle",  "jm"); break; }
            case More:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "jm", "jle"); break; }
            case MoreEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jme",  "jl"); break; }

            default: { CreateAsm (current -> children ()[0], write); break; }
        }

        //FPRINTF (write, "push 0\n");
        //FPRINTF (write, "cmp_f\n");

        //size_t copy_1 = jmp_++;
        //size_t copy_2 = jmp_++;
        //size_t copy_3 = jmp_++;

        //FPRINTF (write, "jne %d\n", copy_1);
        //FPRINTF (write, "je %d\n",  copy_2);

        //FPRINTF (write, "label %d\n", copy_1);

        CreateAsm (current -> children ()[1], write);
        size_t theGreatCopy = jmp_++;

        size_t if_exit = jmp_++;
        FPRINTF (write, "jmp %d\n", /*copy_3*/ if_exit);

        FPRINTF (write, "label %d\n", /*copy_2*/ theGreatCopy);

        if (current -> size () == 3)
            CreateAsm (current -> children ()[2], write);

        FPRINTF (write, "label %d\n", /*copy_3*/ if_exit);
    })
}

//===============================================================================

void CodeGeneration :: give_While (AstNode* current, FILE* write)
{
    BLOCK ("While",
    {
        size_t copy_1 = jmp_++;
        //size_t copy_2 = jmp_++;
        //size_t copy_3 = jmp_++;

        FPRINTF (write, "label %d\n", copy_1);

        switch (current -> children ()[0] -> key ().type)
        {
            case Equal:     { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "je", "jne"); break; }
            case NotEqual:  { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jne",  "je"); break; }
            case Less:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "jl", "jme"); break; }
            case LessEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jle",  "jm"); break; }
            case More:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write,  "jm", "jle"); break; }
            case MoreEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], write, "jme",  "jl"); break; }

            default: { CreateAsm (current -> children ()[0], write); break; }
        }

        //FPRINTF (write, "push 0\n");
        //FPRINTF (write, "cmp_f\n");

        //FPRINTF (write, "jne %d\n", copy_2);
        //FPRINTF (write, "je %d\n",  copy_3);

        //FPRINTF (write, "label %d\n", copy_2);

        size_t theGreatCopy = jmp_++;

        CreateAsm (current -> children ()[1], write);

        FPRINTF (write, "jmp %d\n", copy_1);

        FPRINTF (write, "label %d\n", /*copy_3*/ theGreatCopy);
    })
}

//===============================================================================

void CodeGeneration :: give_Digit (AstNode* current, FILE* write)
{
    FPRINTF (write, "push %d\n", current -> key ().value);
}

//===============================================================================

void CodeGeneration :: give_Name (AstNode* current, FILE* write)
{
    FPRINTF (write, "push %%%d\n", current -> key ().value);
}

//===============================================================================

void CodeGeneration :: give_Block (AstNode* current, FILE* write)
{
    for (size_t i = 0; i < size_ram_; i++)
    {
        FPRINTF (write, "push %%%d\n", i);
    }

    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (int i = size_ram_ - 1; i >= 0; i--)
    {
        FPRINTF (write, "pop %%%d\n", i);
    }
}

//===============================================================================

void CodeGeneration :: give_DeclFunc (AstNode* current, FILE* write)
{
    if (current -> size () == 4) //TODO: FIND bug with label++
    {
        BLOCK ("Function",
        {
            FPRINTF (write, "label %d\n\n", current -> children ()[1] -> key ().value);

            BLOCK ("System",
            {
                FPRINTF (write, "push bp\n");
                FPRINTF (write, "mov bp, sp\n");
            })

            BLOCK ("Params",
            {
                for (size_t i = 0; i < current -> children ()[2] -> size (); i++) //How many params
                {
                    FPRINTF (write, "push $%d\n", i + 1);
                    FPRINTF (write, "pop %%%d\n", current -> children ()[2] -> children ()[i] -> children ()[1] -> key ().value);

                    if (i < current -> children ()[2] -> size () - 1)
                    {
                        FPRINTF (write, "\n");
                    }
                }
            })

            for (size_t i = 0; i < current -> children ()[3] -> size (); i++)
                CreateAsm (current -> children ()[3] -> children ()[i], write);

            FPRINTF (write, "ret\n");
        })

    }
}

//===============================================================================

void CodeGeneration :: give_DeclVar (AstNode* current, FILE* write)
{
    size_ram_ = current -> children ()[1] -> key ().value;

    CreateAsm (current -> children ()[2], write);

    FPRINTF (write, "pop %%%d\n", size_ram_);

    FPRINTF (write, "\n");
}

//===============================================================================

void CodeGeneration :: give_Call (AstNode* current, FILE* write)
{
    BLOCK ("Call",
    {
        for (size_t i = 0; i </*=*/ size_ram_; i++)
        {
            FPRINTF (write, "push %%%d\n", i);
        }

        FPRINTF (write, "\n");

        BLOCK ("Params",
        {
            for (size_t i = 0; i < current -> children ()[1] -> size (); i++)
                CreateAsm (current -> children ()[1] -> children ()[i], write);
        })

        FPRINTF (write, "call %d\n", current -> children ()[0] -> key ().value);

        FPRINTF (write, "\n");

        for (int i = size_ram_; i >= 0; i--)
        {
            FPRINTF (write, "pop %%%d\n", i);
        }

        FPRINTF (write, "\n");

        FPRINTF (write, "push ax\n");
    })
}

//===============================================================================

void CodeGeneration :: give_Return (AstNode* current, FILE* write)
{
    BLOCK ("Return",
    {
        //FPRINTF (write, "\n");

        CreateAsm (current -> children ()[0], write);

        FPRINTF (write, "pop ax\n");
        FPRINTF (write, "pop bp\n"); //
    })
}

//===============================================================================

void CodeGeneration :: give_Out (AstNode* current, FILE* write)
{
    BLOCK ("Out",
    {
        CreateAsm (current -> children ()[0], write);

        FPRINTF (write, "pop bx\n");
        FPRINTF (write, "out bx\n");
    })
}

#endif
