#ifndef CodeGeneration_hpp

#define CodeGeneration_hpp

#include <cstdio>
#include <iostream>
#include "..//..//Libraries//FormatFile.hpp"

#define BLOCK(comment, code)\
file_.print (";{==========%s\n", comment);\
file_.increase ();\
\
    code \
\
file_.decrease ();\
file_.print (";}==========%s\n\n", comment);

class CodeGeneration
{
    public:
        CodeGeneration (const size_t func);

        void parsing (AstNode& root);

    private:
        size_t jmp_;

        int size_ram_;

        size_t count_;

        FormatFile file_;

        void CreateAsm                                         (AstNode* current);
        void give_Add_Sub_Mul_Div_Mod                          (AstNode* current, const char* command);
        void give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (AstNode* current, const char* if_comand, const char* else_comand);
        void give_And                                          (AstNode* current);
        void give_Or                                           (AstNode* current);
        void give_Assignment                                   (AstNode* current);
        void give_If                                           (AstNode* current);
        void give_While                                        (AstNode* current);
        void give_Declaration                                  (AstNode* current);
        void give_Digit                                        (AstNode* current);
        void give_Name                                         (AstNode* current);
        void give_Block                                        (AstNode* current);
        void give_DeclFunc                                     (AstNode* current);
        void give_DeclVar                                      (AstNode* current);
        void give_Call                                         (AstNode* current);
        void give_Return                                       (AstNode* current);
        void give_Out                                          (AstNode* current);
};

CodeGeneration::CodeGeneration (const size_t func):
    jmp_      (func + 1),
    size_ram_ (0),
    count_    (0),
    file_     ()
{
}

void CodeGeneration::parsing (AstNode& root)
{
    const int number_of_main = 0;

    file_.print ("call %d\n", number_of_main);
    file_.print ("eof\n\n");

    for (size_t i = 0; i < root.size (); i++)
    {
        size_ram_ = 0;

        CreateAsm (root[i]);
    }
}

void CodeGeneration::CreateAsm (AstNode* current)
{
    #define DEER(id, name, word, code) case id: { code break; }

    switch (current -> key ().type)
    {
        #include "CList.inl"

        default: { std::cout << current -> key ().type << "\n"; throw "default: error"; }
    }

    #undef DEER
}

void CodeGeneration::give_Add_Sub_Mul_Div_Mod (AstNode* current, const char* command)
{
    BLOCK ("Actions",
    {
        for (int i = current -> size () - 1; i >= 0; i--)
            CreateAsm (current -> children ()[i]);

        for (size_t i = 0; i < current -> size () - 1; i++)
            file_.print ("%s\n", command);
    })
}

void CodeGeneration::give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (AstNode* current, const char* if_comand, const char* else_comand)
{
    for (int i = current -> size () - 1; i >= 0; i--)
        CreateAsm (current -> children ()[i]);

    file_.print ("cmp_f\n");

    for (size_t i = 0; i < current -> size (); i++)
        file_.print ("pop\n");

    size_t copy_1 = jmp_++;
    size_t copy_2 = jmp_;//++
    //size_t copy_3 = jmp_++;

    file_.print ("%s %d\n",   if_comand, copy_1);
    file_.print ("%s %d\n", else_comand, copy_2);

    file_.print ("label %d\n",           copy_1);

    /*file_.print ("push 1\n");
    file_.print ("jmp %d\n",             copy_3);

    file_.print ("label %d\n",           copy_2);

    file_.print ("push 0\n");

    file_.print ("label %d\n",           copy_3);*/
}

void CodeGeneration::give_And (AstNode* current)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i]);

    for (size_t i = 0; i < current -> size () - 1; i++)
        file_.print ("mul\n");
}

void CodeGeneration::give_Or (AstNode* current)
{
    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i]);

    for (size_t i = 0; i < current -> size () - 1; i++)
        file_.print ("add\n");
}

void CodeGeneration::give_Assignment (AstNode* current)
{
    CreateAsm (current -> children ()[current -> children ().size () - 1]);

    for (size_t i = 0; i < current -> children ().size () - 1; i++)
    {
        file_.print ("dup\n");

        file_.print ("pop %%%d\n", current -> children ()[i] -> key ().value);
    }

    file_.print ("pop\n");
}

void CodeGeneration::give_If (AstNode* current)
{
    BLOCK ("If",
    {
        switch (current -> children ()[0] -> key ().type)
        {
            case Equal:     { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "je", "jne"); break; }
            case NotEqual:  { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jne",  "je"); break; }
            case Less:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "jl", "jme"); break; }
            case LessEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jle",  "jm"); break; }
            case More:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "jm", "jle"); break; }
            case MoreEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jme",  "jl"); break; }

            default: { CreateAsm (current -> children ()[0]); break; }
        }

        //file_.print ("push 0\n");
        //file_.print ("cmp_f\n");

        //size_t copy_1 = jmp_++;
        //size_t copy_2 = jmp_++;
        //size_t copy_3 = jmp_++;

        //file_.print ("jne %d\n", copy_1);
        //file_.print ("je %d\n",  copy_2);

        //file_.print ("label %d\n", copy_1);

        CreateAsm (current -> children ()[1]);
        size_t theGreatCopy = jmp_++;

        size_t if_exit = jmp_++;
        file_.print ("jmp %d\n", /*copy_3*/ if_exit);

        file_.print ("label %d\n", /*copy_2*/ theGreatCopy);

        if (current -> size () == 3)
            CreateAsm (current -> children ()[2]);

        file_.print ("label %d\n", /*copy_3*/ if_exit);
    })
}

void CodeGeneration::give_While (AstNode* current)
{
    BLOCK ("While",
    {
        size_t copy_1 = jmp_++;
        //size_t copy_2 = jmp_++;
        //size_t copy_3 = jmp_++;

        file_.print ("label %d\n", copy_1);

        switch (current -> children ()[0] -> key ().type)
        {
            case Equal:     { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "je", "jne"); break; }
            case NotEqual:  { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jne",  "je"); break; }
            case Less:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "jl", "jme"); break; }
            case LessEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jle",  "jm"); break; }
            case More:      { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0],  "jm", "jle"); break; }
            case MoreEqual: { give_Equal_NotEqual_Less_LessEqual_More_MoreEqual (current -> children ()[0], "jme",  "jl"); break; }

            default: { CreateAsm (current -> children ()[0]); break; }
        }

        //file_.print ("push 0\n");
        //file_.print ("cmp_f\n");

        //file_.print ("jne %d\n", copy_2);
        //file_.print ("je %d\n",  copy_3);

        //file_.print ("label %d\n", copy_2);

        size_t theGreatCopy = jmp_++;

        CreateAsm (current -> children ()[1]);

        file_.print ("jmp %d\n", copy_1);

        file_.print ("label %d\n", /*copy_3*/ theGreatCopy);
    })
}

void CodeGeneration::give_Digit (AstNode* current)
{
    file_.print ("push %d\n", current -> key ().value);
}

void CodeGeneration::give_Name (AstNode* current)
{
    file_.print ("push %%%d\n", current -> key ().value);
}

void CodeGeneration::give_Block (AstNode* current)
{
    for (size_t i = 0; i < size_ram_; i++)
    {
        file_.print ("push %%%d\n", i);
    }

    for (size_t i = 0; i < current -> size (); i++)
        CreateAsm (current -> children ()[i]);

    for (int i = size_ram_ - 1; i >= 0; i--)
    {
        file_.print ("pop %%%d\n", i);
    }
}

void CodeGeneration::give_DeclFunc (AstNode* current)
{
    if (current -> size () == 4) //TODO: FIND bug with label++
    {
        BLOCK ("Function",
        {
            file_.print ("label %d\n\n", current -> children ()[1] -> key ().value);

            BLOCK ("System",
            {
                file_.print ("push bp\n");
                file_.print ("mov bp, sp\n");
            })

            BLOCK ("Params",
            {
                for (size_t i = 0; i < current -> children ()[2] -> size (); i++) //How many params
                {
                    file_.print ("push $%d\n", i + 1);
                    file_.print ("pop %%%d\n", current -> children ()[2] -> children ()[i] -> children ()[1] -> key ().value);

                    if (i < current -> children ()[2] -> size () - 1)
                    {
                        file_.print ("\n");
                    }
                }
            })

            for (size_t i = 0; i < current -> children ()[3] -> size (); i++)
                CreateAsm (current -> children ()[3] -> children ()[i]);

            file_.print ("ret\n");
        })

    }
}

void CodeGeneration::give_DeclVar (AstNode* current)
{
    size_ram_ = current -> children ()[1] -> key ().value;

    CreateAsm (current -> children ()[2]);

    file_.print ("pop %%%d\n", size_ram_);

    file_.print ("\n");
}

void CodeGeneration::give_Call (AstNode* current)
{
    BLOCK ("Call",
    {
        for (size_t i = 0; i </*=*/ size_ram_; i++)
        {
            file_.print ("push %%%d\n", i);
        }

        file_.print ("\n");

        BLOCK ("Params",
        {
            for (size_t i = 0; i < current -> children ()[1] -> size (); i++)
                CreateAsm (current -> children ()[1] -> children ()[i]);
        })

        file_.print ("call %d\n", current -> children ()[0] -> key ().value);

        file_.print ("\n");

        for (int i = size_ram_; i >= 0; i--)
        {
            file_.print ("pop %%%d\n", i);
        }

        file_.print ("\n");

        file_.print ("push ax\n");
    })
}

void CodeGeneration::give_Return (AstNode* current)
{
    BLOCK ("Return",
    {
        //file_.print ("\n");

        CreateAsm (current -> children ()[0]);

        file_.print ("pop ax\n");
        file_.print ("pop bp\n"); //
    })
}

void CodeGeneration::give_Out (AstNode* current)
{
    BLOCK ("Out",
    {
        CreateAsm (current -> children ()[0]);

        file_.print ("pop bx\n");
        file_.print ("out bx\n");
    })
}

#undef BLOCK

#endif /* CodeGeneration_hpp */
