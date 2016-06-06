#ifndef CodeGeneration_hpp
    #define CodeGeneration_hpp

//{==============================================================================

#include <cstdio>
#include <iostream>

//}==============================================================================

//{==============================================================================

class CodeGeneration
{
    private:
        size_t jmp_;

        int size_ram_;

    public:
        CodeGeneration (AstNode& root, FILE* write, const size_t func);

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
    jmp_      (func),
    size_ram_ (0)
    {
        jmp_++; //

        fprintf (write, "call %d\n", 0);
        fprintf (write, "eof\n");

        for (size_t i = 0; i < root.size (); i++)
        {
            size_ram_ = 0;

            CreateAsm (root[i], write);
        }
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
    fprintf (write, "\n;{========== a %s b\n", command);

    for (int i = current -> size () - 1; i >= 0; i--)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> size () - 1; i++)
        fprintf (write, "%s\n", command);

    fprintf (write, ";}========== a %s b\n", command);
}

//===============================================================================

void CodeGeneration :: give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (AstNode* current, FILE* write, const char* if_comand, const char* else_comand)
{
    fprintf (write, "\n;{========== a <=> b\n");

    for (int i = current -> size () - 1; i >= 0; i--)
        CreateAsm (current -> children ()[i], write);

    fprintf (write, "cmp_f\n");

    for (size_t i = 0; i < current -> size (); i++)
        fprintf (write, "pop\n");

    size_t copy_1 = jmp_++;
    size_t copy_2 = jmp_;//++
    //size_t copy_3 = jmp_++;

    fprintf (write, "%s %d\n",   if_comand, copy_1);
    fprintf (write, "%s %d\n", else_comand, copy_2);

    fprintf (write, "label %d\n",           copy_1);

    /*fprintf (write, "push 1\n");
    fprintf (write, "jmp %d\n",             copy_3);

    fprintf (write, "label %d\n",           copy_2);

    fprintf (write, "push 0\n");

    fprintf (write, "label %d\n",           copy_3);*/

    fprintf (write, ";}========== a <=> b\n");
}

//===============================================================================

void CodeGeneration :: give_And (AstNode* current, FILE* write)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> size () - 1; i++)
        fprintf (write, "mul\n");
}

//===============================================================================

void CodeGeneration :: give_Or (AstNode* current, FILE* write)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> size () - 1; i++)
        fprintf (write, "add\n");
}

//===============================================================================

void CodeGeneration :: give_Assignment (AstNode* current, FILE* write)
{
    fprintf (write, "\n;{========== a = b");

    CreateAsm (current -> children ()[current -> children ().size () - 1], write);

    for (size_t i = 0; i < current -> children ().size () - 1; i++)
    {
        fprintf (write, "dup\n");

        fprintf (write, "pop %%%d\n", current -> children ()[i] -> key ().value);
    }

    fprintf (write, "pop\n");

    fprintf (write, ";}========== a = b\n");
}

//===============================================================================

void CodeGeneration :: give_If (AstNode* current, FILE* write)
{
    fprintf (write, "\n;{========== if\n");

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

    //fprintf (write, "push 0\n");
    //fprintf (write, "cmp_f\n");

    //size_t copy_1 = jmp_++;
    //size_t copy_2 = jmp_++;
    //size_t copy_3 = jmp_++;

    //fprintf (write, "jne %d\n", copy_1);
    //fprintf (write, "je %d\n",  copy_2);

    //fprintf (write, "label %d\n", copy_1);

    CreateAsm (current -> children ()[1], write);
    size_t theGreatCopy = jmp_++;

    size_t if_exit = jmp_++;
    fprintf (write, "jmp %d\n", /*copy_3*/ if_exit);

    fprintf (write, "label %d\n", /*copy_2*/ theGreatCopy);

    if (current -> size () == 3)
        CreateAsm (current -> children ()[2], write);

    fprintf (write, "label %d\n", /*copy_3*/ if_exit);

    fprintf (write, ";}========== if\n");
}

//===============================================================================

void CodeGeneration :: give_While (AstNode* current, FILE* write)
{
    fprintf (write, "\n;{========== while\n");

    size_t copy_1 = jmp_++;
    //size_t copy_2 = jmp_++;
    //size_t copy_3 = jmp_++;

    fprintf (write, "label %d\n", copy_1);

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

    //fprintf (write, "push 0\n");
    //fprintf (write, "cmp_f\n");

    //fprintf (write, "jne %d\n", copy_2);
    //fprintf (write, "je %d\n",  copy_3);

    //fprintf (write, "label %d\n", copy_2);

    size_t theGreatCopy = jmp_++;

    CreateAsm (current -> children ()[1], write);

    fprintf (write, "jmp %d\n", copy_1);

    fprintf (write, "label %d\n", /*copy_3*/ theGreatCopy);

    fprintf (write, ";}========== while\n");
}

//===============================================================================

void CodeGeneration :: give_Digit (AstNode* current, FILE* write)
{
    fprintf (write, "push %d\n", current -> key ().value);
}

//===============================================================================

void CodeGeneration :: give_Name (AstNode* current, FILE* write)
{
    fprintf (write, "push %%%d\n", current -> key ().value);
}

//===============================================================================

void CodeGeneration :: give_Block (AstNode* current, FILE* write)
{
    fprintf (write, "\n;{========== {");

    for (size_t i = 0; i < size_ram_; i++)
        fprintf (write, "push %%%d\n", i);

    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (int i = size_ram_ - 1; i >= 0; i--)
        fprintf (write, "pop %%%d\n", i);

    fprintf (write, "\n;{========== }\n");
}

//===============================================================================

void CodeGeneration :: give_DeclFunc (AstNode* current, FILE* write)
{
    if (current -> size () == 4) //TODO: FIND bug with label++
    {
        fprintf (write, "\n");
        fprintf (write, "label %d\n\n", current -> children ()[1] -> key ().value);

        fprintf (write, "push bp\n");
        fprintf (write, "mov bp, sp\n\n");

        for (size_t i = 0; i < current -> children ()[2] -> size (); i++) //How many params
        {
            fprintf (write, "push $%d\n", i + 1);
            fprintf (write, "pop %%%d\n", current -> children ()[2] -> children ()[i] -> children ()[1] -> key ().value);
        }

        for (size_t i = 0; i < current -> children ()[3] -> size (); i++)
            CreateAsm (current -> children ()[3] -> children ()[i], write);

        fprintf (write, "\nret\n");
    }
}

//===============================================================================

void CodeGeneration :: give_DeclVar (AstNode* current, FILE* write)
{
    size_ram_ = current -> children ()[1] -> key ().value;

    CreateAsm (current -> children ()[2], write);

    fprintf (write, "pop %%%d\n", size_ram_);

    fprintf (write, "\n");
}

//===============================================================================

void CodeGeneration :: give_Call (AstNode* current, FILE* write)
{
    for (size_t i = 0; i <= size_ram_; i++)
        fprintf (write, "   push %%%d\n", i);

    fprintf (write, "\n");

    for (size_t i = 0; i < current -> children ()[1] -> size (); i++)
        CreateAsm (current -> children ()[1] -> children ()[i], write);

    fprintf (write, "\n");

    fprintf (write, "call %d\n", current -> children ()[0] -> key ().value);

    fprintf (write, "\n");

    for (int i = size_ram_; i >= 0; i--)
        fprintf (write, "   pop %%%d\n", i);

    fprintf (write, "\n");

    fprintf (write, "push ax\n");
}

//===============================================================================

void CodeGeneration :: give_Return (AstNode* current, FILE* write)
{
    fprintf (write, "\n");

    CreateAsm (current -> children ()[0], write);

    fprintf (write, "pop ax\n");
}

//===============================================================================

void CodeGeneration :: give_Out (AstNode* current, FILE* write)
{
    fprintf (write, "\n");

    CreateAsm (current -> children ()[0], write);

    fprintf (write, "pop bx\n");
    fprintf (write, "out bx\n");
}

#endif
