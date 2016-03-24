#ifndef TreeCheck_hpp
    #define TreeCheck_hpp

//TODO: counting size of RAM in Boa

class SemanticAnalyzer
{
    private:
        Vector <int> data_;

    public:
        SemanticAnalyzer (AstNode& root, LogHTML& log);

        void Detour (AstNode* current, LogHTML& log);

        void Check_Block   (AstNode* current, LogHTML& log);
        void Check_DeclVar (AstNode* current, LogHTML& log);
        void Check_Name    (AstNode* current, LogHTML& log);
};

SemanticAnalyzer :: SemanticAnalyzer (AstNode& root, LogHTML& log):
    data_     ()
    {
        data_.push_back (-1);

        for (size_t i = 0; i < root.size (); i++)
            Detour (root[i], log);
    }

void SemanticAnalyzer :: Detour (AstNode* current, LogHTML& log)
{
    switch (current -> key ().type)
    {
        case Block:   { Check_Block   (current, log); break; }
        case DeclVar: { Check_DeclVar (current, log); break; }
        case Name:    { Check_Name    (current, log); break; }

        default:
        {
            for (size_t i = 0; i < current -> children ().size (); i++)
                Detour (current -> children ()[i], log);

            break;
        }
    }
}

void SemanticAnalyzer :: Check_Block (AstNode* current, LogHTML& log)
{
    data_.push_back (-1);

    for (size_t i = 0; i < current -> size (); i++)
        Detour (current[i], log);

    while (data_.back () != -1) data_.pop_back ();
}

void SemanticAnalyzer :: Check_DeclVar (AstNode* current, LogHTML& log)
{
    int deskriptor = current -> children ()[1] -> key ().value;

    for (size_t i = data_.size () - 1; data_[i] != 0; i--)
    {
        if (data_[i] == deskriptor)
        {
            log.output ("Variable var_%d was declared before\n", deskriptor);
        }
    }

    data_.push_back (deskriptor);

    Detour (current -> children ()[2], log);
}

void SemanticAnalyzer :: Check_Name (AstNode* current, LogHTML& log)
{
    int deskriptor = current -> key ().value;

    bool first = false;
    for (size_t i = data_.size () - 1; data_[i] != 0; i--)
    {
        if (data_[i] == deskriptor) first = true;
    }

    if (!first)
    {
        log.output ("Variable var_%d wasn't declared before\n", deskriptor);
    }
}

#endif
