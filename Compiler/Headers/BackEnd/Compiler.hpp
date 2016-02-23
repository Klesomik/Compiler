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

        case Assignment: { DETOUR fprintf (write, "pop %c%d;\n", '%', current -> key ().value); break; }
        case Digit:      { fprintf (write, "push %d;\n", current -> key ().value); break; }
        case Var:        { return; }
        case None:       { DETOUR break; }

        case Equal:      { DETOUR fprintf (write, "push %c%d;\n", '%', current -> key ().value); fprintf (write, "sub;\n"); break; }
        case    If:
        {
            CreateAsm (current -> children ()[0], write);

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

        default:         { cout << current -> key ().type << "\n"; throw "default: error"; }
    }
}
