#pragma once

//{==============================================================================

#define DETOUR \
for (size_t i = 0; i < current -> children ().size (); i++)\
    CreateAsm (current -> children ()[i], write);

//}==============================================================================

//{==============================================================================

void CreateAsm (AstNode* current, FILE* write);

//}==============================================================================

void CreateAsm (AstNode* current, FILE* write)
{
    static int jmp = 0;

    switch (current -> key ().type)
    {
        case Add:        { DETOUR fprintf (write, "add;\n"); break; }
        case Sub:        { DETOUR fprintf (write, "sub;\n"); break; }
        case Mul:        { DETOUR fprintf (write, "mul;\n"); break; }
        case Div:        { DETOUR fprintf (write, "div;\n"); break; }
        case Mod:        { DETOUR fprintf (write, "mod;\n"); break; }

        case Assignment:
        {
            int var_value = 0;
            if (current -> children ()[0] -> key ().type == Var)
                var_value = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> children ().size (); i++)
                CreateAsm (current -> children ()[i], write);

            fprintf (write, "pop %c%d;\n", '%', var_value);

            break;
        }

        case Digit:      { fprintf (write, "push %d;\n", current -> key ().value); break; }
        case Var:        { fprintf (write, "push %c%d;\n", '%', current -> key ().value); break; }
        case None:       { DETOUR break; }

        case Equal:      { DETOUR fprintf (write, "sub;\n"); break; }
        case    If:
        {
            CreateAsm (current -> children ()[0], write);

            fprintf (write, "push 0;\n");
            fprintf (write, "sub;\n");

            int copy = jmp++;
            fprintf (write, "jne %d;\n", copy);

            CreateAsm (current -> children ()[1], write);

            int tmp = jmp++;
            fprintf (write, "jmp %d;\n", tmp);
            fprintf (write, "label %d;\n", copy);

            if (current -> children ().size () > 2) CreateAsm (current -> children ()[2], write);
            fprintf (write, "label %d;\n", tmp);

            break;
        }

        case While:
        {
            CreateAsm (current -> children ()[0], write);

            fprintf (write, "push 0;\n");
            fprintf (write, "sub;\n");

            int copy_1 = jmp++;
            fprintf (write, "label %d;\n", copy_1);

            int copy_2 = jmp++;
            fprintf (write, "jne %d;\n", copy_2);

            CreateAsm (current -> children ()[1], write);

            fprintf (write, "jmp %d;\n", copy_1);
            fprintf (write, "label %d;\n", copy_2);

            break;
        }

        default:         { cout << current -> key ().type << "\n"; throw "default: error"; }
    }
}
