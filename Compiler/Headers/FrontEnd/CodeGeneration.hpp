#ifndef CodeGeneration_hpp
    #define CodeGeneration_hpp

#include <cstdio>
#include <iostream>

class CodeGeneration
{
    private:
        int jmp_;

    public:
        CodeGeneration (AstNode& root, FILE* write);

        void CreateAsm                (AstNode* current, FILE* write);
        void Give_Add_Sub_Mul_Div_Mod (AstNode* current, FILE* write, const char* command);
        void Give_Assignment          (AstNode* current, FILE* write);
        void Give_If                  (AstNode* current, FILE* write);
        void Give_While               (AstNode* current, FILE* write);
        void Give_Declaration         (AstNode* current, FILE* write);
};

CodeGeneration :: CodeGeneration (AstNode& root, FILE* write):
    jmp_ (0)
    {
        for (size_t i = 0; i < root.size (); i++)
            CreateAsm (root[i], write);
    }

void CodeGeneration :: CreateAsm (AstNode* current, FILE* write)
{
    switch (current -> key ().type)
    {
        //case Add: { Give_Add_Sub_Mul_Div_Mod (current, write, "add"); break; }
        //case Sub: { Give_Add_Sub_Mul_Div_Mod (current, write, "sub"); break; }
        //case Mul: { Give_Add_Sub_Mul_Div_Mod (current, write, "mul"); break; }
        //case Div: { Give_Add_Sub_Mul_Div_Mod (current, write, "div"); break; }
        //case Mod: { Give_Add_Sub_Mul_Div_Mod (current, write, "mod"); break; }

        //case Assignment:  { Give_Assignment (current, write); break; }

        case Digit:       { fprintf (write, "push %d;\n", current -> key ().value); break; }
        //case Var:         { fprintf (write, "push %c%d;\n", '%', current -> key ().value); break; }
        //case None:        { for (size_t i = 0; i < current -> children ().size (); i++) CreateAsm (current -> children ()[i], write); break; }

        case Equal:       { for (size_t i = 0; i < current -> children ().size (); i++) CreateAsm (current -> children ()[i], write); fprintf (write, "sub;\n"); break; }
        //case    If:       { Give_If (current, write, jmp_); break; }

        //case While:       { Give_While (current, write, jmp_); break; }

        //case Declaration: { Give_Declaration (current, write); break; }
        case Int:         { break; }

        default:          { cout << current -> key ().type << "\n"; throw "default: error"; }
    }
}

void CodeGeneration :: Give_Add_Sub_Mul_Div_Mod (AstNode* current, FILE* write, const char* command)
{
    for (size_t i = 0; i < current -> children ().size (); i++)
        CreateAsm (current -> children ()[i], write);

    for (size_t i = 0; i < current -> children ().size () - 1; i++)
        fprintf (write, "%s;\n", command);
}

void CodeGeneration :: Give_Assignment (AstNode* current, FILE* write)
{
    int var_value = 0;
    //if (current -> children ()[0] -> key ().type == Var)
        //var_value = current -> children ()[0] -> key ().value;

    for (size_t i = 1; i < current -> children ().size (); i++)
        CreateAsm (current -> children ()[i], write);

    fprintf (write, "pop %c%d;\n", '%', var_value);
}

void CodeGeneration :: Give_If (AstNode* current, FILE* write)
{
    CreateAsm (current -> children ()[0], write);

    fprintf (write, "push 0;\n");
    fprintf (write, "sub;\n");

    int copy = jmp_++;
    fprintf (write, "jne %d;\n", copy);

    CreateAsm (current -> children ()[1], write);

    int tmp = jmp_++;
    fprintf (write, "jmp %d;\n", tmp);
    fprintf (write, "label %d;\n", copy);

    if (current -> children ().size () > 2) CreateAsm (current -> children ()[2], write);
    fprintf (write, "label %d;\n", tmp);
}

void CodeGeneration :: Give_While (AstNode* current, FILE* write)
{
    CreateAsm (current -> children ()[0], write);

    fprintf (write, "push 0;\n");
    fprintf (write, "sub;\n");

    int copy_1 = jmp_++;
    fprintf (write, "label %d;\n", copy_1);

    int copy_2 = jmp_++;
    fprintf (write, "jne %d;\n", copy_2);

    CreateAsm (current -> children ()[1], write);

    fprintf (write, "jmp %d;\n", copy_1);
    fprintf (write, "label %d;\n", copy_2);
}

void CodeGeneration :: Give_Declaration (AstNode* current, FILE* write)
{
    CreateAsm (current -> children ()[0], write);
    CreateAsm (current -> children ()[2], write);

    fprintf (write, "pop %c%d;\n", '%', current -> children ()[1] -> key ().value);
}

#endif
