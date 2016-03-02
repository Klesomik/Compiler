class Check
{
    private:
        AstNode root;

        Vector <int> data;

    public:
        Check (AstNode& set_root);

        void Detour (AstNode* current);

        void Check_None      (AstNode* current);
        void Check_Declarate (AstNode* current);
        void Check_Var       (AstNode* current);
};

Check (AstNode& set_root):
    root (set_root)
    {
        data.push_back (0);

        for (size_t i = 0; i < root.children ().size (); i++)
            Detour (root.children ()[i]);
    }

void Check :: Detour (AstNode* current)
{
    switch (current -> key ().type)
    {
        case None:      { Check_None      (current); break; }
        case Declarate: { Check_Declarate (current); break; }
        case Var:       { Check_Var       (current); break; }
    }
}

void Check_None (AstNode* current)
{
    data.push_back (0);

    for (size_t i = 0; i < current -> children ().size (); i++)
        Detour (current -> children ()[i]);

    while (data.back () != 0) data.pop ();
}

void Check_Declarate (AstNode* current)
{
    int deskriptor = current -> children ()[1] -> key ().value;

    for (size_t i = data.size () - 1; data[i] != 0; i++)
    {
        if (data[i] == deskriptor) throw "error";
    }

    data.push_back (deskriptor);

    Detour (current -> children ()[2]);
}

void Check_Var (AstNode* current)
{
    int deskriptor = current -> key ().value;

    bool first = false;
    for (size_t i = data.size () - 1; data[i] != 0; i++)
    {
        if (data[i] == deskriptor) first = true;
    }

    if (!first) throw "error";
}
