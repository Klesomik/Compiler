#ifndef TreeCheck_hpp
    #define TreeCheck_hpp

class SemanticAnalyzer
{
    private:
        Vector <int> data_;

        size_t error_;

    public:
        SemanticAnalyzer (AstNode& root);

        void Detour (AstNode* current);

        void Check_None      (AstNode* current);
        void Check_Declarate (AstNode* current);
        void Check_Var       (AstNode* current);
};

SemanticAnalyzer :: SemanticAnalyzer (AstNode& root):
    data_  (),
    error_ (0)
    {
        data_.push_back (0);

        Inform.log_file.setFontColor ("black");
        Inform.log_file.setSize (1200);
        Inform.log_file.setColor ("yellow");

        for (size_t i = 0; i < root.children ().size (); i++)
            Detour (root.children ()[i]);

        Inform.log_file.output ("=== Build finished: %d errors ===\n", error_);
    }

void SemanticAnalyzer :: Detour (AstNode* current)
{
    switch (current -> key ().type)
    {
        case None:        { Check_None      (current); break; }
        case Declaration: { Check_Declarate (current); break; }
        case Var:         { Check_Var       (current); break; }

        default:
        {
            for (size_t i = 0; i < current -> children ().size (); i++)
                Detour (current -> children ()[i]);

            break;
        }
    }
}

void SemanticAnalyzer :: Check_None (AstNode* current)
{
    data_.push_back (0);

    for (size_t i = 0; i < current -> children ().size (); i++)
        Detour (current -> children ()[i]);

    while (data_.back () != 0) data_.pop ();
}

void SemanticAnalyzer :: Check_Declarate (AstNode* current)
{
    int deskriptor = current -> children ()[1] -> key ().value;

    for (size_t i = data_.size () - 1; data_[i] != 0; i--)
    {
        if (data_[i] == deskriptor)
        {
            Inform.log_file.output ("Variable var_%d was declared before\n", deskriptor);

            error_++;
        }
    }

    data_.push_back (deskriptor);

    Detour (current -> children ()[2]);
}

void SemanticAnalyzer :: Check_Var (AstNode* current)
{
    int deskriptor = current -> key ().value;

    bool first = false;
    for (size_t i = data_.size () - 1; data_[i] != 0; i--)
    {
        if (data_[i] == deskriptor) first = true;
    }

    if (!first)
    {
        Inform.log_file.output ("Variable var_%d wasn't declared before\n", deskriptor);

        error_++;
    }
}

#endif
