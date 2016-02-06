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

    else if (current.key ().type_ == Equal)
    {
        CreateAsmTree (current.left  (), write);
        CreateAsmTree (current.right (), write);

        char del = '%';
        fprintf (write, "pop %c%d;\n", del, current.key ().value_);

        return;
    }

    else if (current.key ().type_ == Digit)
    {
        fprintf (write, "push %d;\n", current.key ().value_);

        return;
    }

    else if (current.key ().type_ == Var)
    {
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

    else if (current -> key ().type_ == Equal)
    {
        CreateAsmTree (current -> left  (), write);
        CreateAsmTree (current -> right (), write);

        char del = '%';
        fprintf (write, "pop %c%d;\n", del, current -> key ().value_);

        return;
    }

    else if (current -> key ().type_ == Digit)
    {
        fprintf (write, "push %d;\n", current -> key ().value_);

        return;
    }

    else if (current -> key ().type_ == Var)
    {
        return;
    }
}
