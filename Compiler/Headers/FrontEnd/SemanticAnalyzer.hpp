#ifndef TreeCheck_hpp
    #define TreeCheck_hpp

#include "..//..//Librarys//AbstractSyntaxNode.hpp"
#include "..//..//Librarys//LogHTML.hpp"

//{==============================================================================

struct FunctionMember
{
    int type, name, args;

    bool code;

    FunctionMember ();
    FunctionMember (const int setType, const int setName, const int setArgs, const bool setCode);
};

//}==============================================================================

FunctionMember :: FunctionMember ():
    type (),
    name (),
    args (),
    code ()
    {}

FunctionMember :: FunctionMember (const int setType, const int setName, const int setArgs, const bool setCode):
    type (setType),
    name (setName),
    args (setArgs),
    code (setCode)
    {}

//{==============================================================================

class SemanticAnalyzer
{
    private:
        Vector <int> data_;
        Vector <FunctionMember> func_;

        size_t label_;

    public:
        SemanticAnalyzer (AstNode& root, LogHTML& log);

        void error (LogHTML& log, const char* message);

        void Detour (AstNode* current, LogHTML& log);

        void Check_Block    (AstNode* current, LogHTML& log);
        void Check_DeclVar  (AstNode* current, LogHTML& log);
        void Check_Name     (AstNode* current, LogHTML& log);
        void Check_DeclFunc (AstNode* current, LogHTML& log);
        void Check_Call     (AstNode* current, LogHTML& log);

        size_t size ();
};

//}==============================================================================

SemanticAnalyzer :: SemanticAnalyzer (AstNode& root, LogHTML& log):
    data_  (),
    func_  (),
    label_ (0)
    {
        try
        {
            data_.push_back (-1);
            label_++;

            for (size_t i = 0; i < root.size (); i++)
                Detour (root.children ()[i], log);
        }
        catch (const char* message)
        {
            std::cout << message << "\n";
        }
    }

//===============================================================================

void SemanticAnalyzer :: error (LogHTML& log, const char* message)
{
    log.output ("%s\n", message);

    throw message;
}

//===============================================================================

void SemanticAnalyzer :: Detour (AstNode* current, LogHTML& log)
{
    switch (current -> key ().type)
    {
        case    Block: { Check_Block    (current, log); break; }
        case  DeclVar: { Check_DeclVar  (current, log); break; }
        case     Name: { Check_Name     (current, log); break; }
        case DeclFunc: { Check_DeclFunc (current, log); break; }
        case     Call: { Check_Call     (current, log); break; }

        default:
        {
            for (size_t i = 0; i < current -> children ().size (); i++)
                Detour (current -> children ()[i], log);

            break;
        }
    }
}

//===============================================================================

void SemanticAnalyzer :: Check_Block (AstNode* current, LogHTML& log)
{
    data_.push_back (-1);
    label_++;

    for (int i = 0; i < current -> size (); i++)
        Detour (current -> children ()[i], log);

    while (data_.back () != -1) data_.pop_back ();

    data_.pop_back ();
    label_--;
}

//===============================================================================

void SemanticAnalyzer :: Check_DeclVar (AstNode* current, LogHTML& log)
{
    int deskriptor = current -> children ()[1] -> key ().value;

    for (int i = data_.size () - 1; data_[i] != -1; i--)
    {
        if (data_[i] == deskriptor)
            error (log, "Variable was declared before\n");
    }

    current -> children ()[1] -> key () = { Name, data_.size () - label_ };
    data_.push_back (deskriptor);

    if (current -> children ()[2]) Detour (current -> children ()[2], log);
}

//===============================================================================

void SemanticAnalyzer :: Check_Name (AstNode* current, LogHTML& log)
{
    int deskriptor = current -> key ().value;

    size_t var = 0;
    bool first = false;
    for (int i = data_.size () - 1; data_[i] != -1; i--)
    {
        if (data_[i] == deskriptor)
        {
            first = true;

            break;
        }

        if (data_[i] != -1) var++;
    }

    current -> key ()  = { Name, data_.size () - label_ - var - 1 };

    if (!first)
        error (log, "Variable wasn't declared before\n");
}

//===============================================================================

void SemanticAnalyzer :: Check_DeclFunc (AstNode* current, LogHTML& log)
{
    int  typeVal = current -> children ()[0] -> key ().type;
    int  nameVal = current -> children ()[1] -> key ().value;
    int  argsVal = current -> children ()[2] -> size ();
    bool codeVal = current -> size () == 4? true : false;

    for (int i = func_.size () - 1; i >= 0; i--)
    {
        if (func_[i].name == nameVal &&
            func_[i].type == typeVal &&
            func_[i].args == argsVal)
        {
            if (func_[i].code == codeVal)
                error (log, "Function was declared before\n");

            if (codeVal) func_[i].code = true;

            //current -> children ()[1] -> key () = { Name, i };

            return;
        }
    }

    data_.push_back (-1);
    label_++;

    //current -> children ()[1] -> key () = { Name, func_.size () };
    func_.push_back ({ typeVal, nameVal, argsVal, codeVal });

    Detour (current -> children ()[2], log);

    if (current -> size () == 4)
    {
        for (int i = 0; i < current -> children ()[3] -> size (); i++)
            Detour (current -> children ()[3] -> children ()[i], log);
    }

    while (data_.back () != -1) data_.pop_back ();

    data_.pop_back ();
    label_--;
}

//===============================================================================

void SemanticAnalyzer :: Check_Call (AstNode* current, LogHTML& log)
{
    int nameVal = current -> children ()[0] -> key ().value;
    int argsVal = current -> children ()[1] -> children ().size ();

    bool first = false;
    for (int i = func_.size () - 1; i >= 0; i--)
    {
        if (func_[i].name == nameVal &&
            func_[i].args == argsVal)
        {
            first = true;

            break;
        }
    }

    //current -> children ()[0] -> key () = { Name, func_.size () };

    if (!first)
        error (log, "Function wasn't declared before\n");
}

//===============================================================================

size_t SemanticAnalyzer :: size ()
{
    return func_.size ();
}

#endif
