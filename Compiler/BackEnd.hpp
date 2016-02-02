void CreateAsm     (BinaryNode <Token>& current, FILE* write);
void CreateAsmTree (BinaryNode <Token>* current, FILE* write);

void CreateAsm     (BinaryNode <Token>& current, FILE* write)
{
     if (current.key ().type_ == Add)
    {
        CreateAsmTree (current.left  (), write);
        CreateAsmTree (current.right (), write);

        fprintf (write, "add;\n");

        return;
    }

    else if (current.key ().type_ == Sub)
    {
        CreateAsmTree (current.left  (), write);
        CreateAsmTree (current.right (), write);

        fprintf (write, "sub;\n");

        return;
    }

    else if (current.key ().type_ == Mul)
    {
        CreateAsmTree (current.left  (), write);
        CreateAsmTree (current.right (), write);

        fprintf (write, "mul;\n");

        return;
    }

    else if (current.key ().type_ == Div)
    {
        CreateAsmTree (current.left  (), write);
        CreateAsmTree (current.right (), write);

        fprintf (write, "div;\n");

        return;
    }

    else
    {
        fprintf (write, "push %d;\n", current.key ().value_);

        return;
    }
}

void CreateAsmTree (BinaryNode <Token>* current, FILE* write)
{
    if (current -> key ().type_ == Add)
    {
        CreateAsmTree (current -> left  (), write);
        CreateAsmTree (current -> right (), write);

        fprintf (write, "add;\n");

        return;
    }

    else if (current -> key ().type_ == Sub)
    {
        CreateAsmTree (current -> left  (), write);
        CreateAsmTree (current -> right (), write);

        fprintf (write, "sub;\n");

        return;
    }

    else if (current -> key ().type_ == Mul)
    {
        CreateAsmTree (current -> left  (), write);
        CreateAsmTree (current -> right (), write);

        fprintf (write, "mul;\n");

        return;
    }

    else if (current -> key ().type_ == Div)
    {
        CreateAsmTree (current -> left  (), write);
        CreateAsmTree (current -> right (), write);

        fprintf (write, "div;\n");

        return;
    }

    else
    {
        fprintf (write, "push %d;\n", current -> key ().value_);

        return;
    }
}
