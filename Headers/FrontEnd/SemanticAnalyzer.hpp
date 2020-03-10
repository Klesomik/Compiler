#ifndef SemanticAnalyzer_hpp

#define SemanticAnalyzer_hpp

#include <vector>
#include "..//..//Libraries//AbstractSyntaxNode.hpp"
#include "..//..//Libraries//LogHTML.hpp"

struct FunctionMember
{
    int type, name, args;

    bool code;

    FunctionMember ();
    FunctionMember (const int setType, const int setName, const int setArgs, const bool setCode);
};

FunctionMember::FunctionMember ():
    type (),
    name (),
    args (),
    code ()
{
}

FunctionMember::FunctionMember (const int setType, const int setName, const int setArgs, const bool setCode):
    type (setType),
    name (setName),
    args (setArgs),
    code (setCode)
{
}

namespace CAP
{
    class SemanticAnalyzer
    {
        public:
            SemanticAnalyzer (AstNode& root, LogHTML& log);

            void parsing ();

        private:
            std::vector <int> data_;
            std::vector <FunctionMember> func_;

            size_t label_;

            void Detour (AstNode* current, LogHTML& log);

            void Check_Block    (AstNode* current, LogHTML& log);
            void Check_DeclVar  (AstNode* current, LogHTML& log);
            void Check_Name     (AstNode* current, LogHTML& log);
            void Check_DeclFunc (AstNode* current, LogHTML& log);
            void Check_Call     (AstNode* current, LogHTML& log);

            size_t size ();
    };
}

CAP::SemanticAnalyzer::SemanticAnalyzer (AstNode& root, LogHTML& log):
    data_  (),
    func_  (),
    label_ (0)
{
}

void CAP::SemanticAnalyzer::parsing ()
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

void CAP::SemanticAnalyzer::Detour (AstNode* current, LogHTML& log)
{
    switch (current->key ().type)
    {
        case    Block: { Check_Block    (current, log); break; }
        case  DeclVar: { Check_DeclVar  (current, log); break; }
        case     Name: { Check_Name     (current, log); break; }
        case DeclFunc: { Check_DeclFunc (current, log); break; }
        case     Call: { Check_Call     (current, log); break; }

        default:
        {
            for (size_t i = 0; i < current->size (); i++)
                Detour (current[i], log);

            break;
        }
    }
}

void CAP::SemanticAnalyzer::Check_Block (AstNode* current, LogHTML& log)
{
    data_.push_back (-1);
    label_++;

    for (int i = 0; i < current->size (); i++)
        Detour (current[i], log);

    while (data_.back () != -1) data_.pop_back ();

    data_.pop_back ();
    label_--;
}

void CAP::SemanticAnalyzer::Check_DeclVar (AstNode* current, LogHTML& log)
{
    int deskriptor = current[1]->key ().value;

    for (int i = data_.size () - 1; data_[i] != -1; i--)
    {
        if (data_[i] == deskriptor)
            LogError (log, "Variable was declared before\n");
    }

    current[1]->key () = { Name, data_.size () - label_ };
    data_.push_back (deskriptor);

    if (current[2]) Detour (current[2], log);
}

void CAP::SemanticAnalyzer::Check_Name (AstNode* current, LogHTML& log)
{
    int deskriptor = current->key ().value;

    size_t var = 0;
    bool flag = false;
    for (int i = data_.size () - 1; data_[i] != -1; i--)
    {
        if (data_[i] == deskriptor)
        {
            flag = true;

            break;
        }

        if (data_[i] != -1) var++;
    }

    current->key ()  = { Name, data_.size () - label_ - var - 1 };

    if (!flag)
        LogError (log, "Variable wasn't declared before\n");
}

void CAP::SemanticAnalyzer::Check_DeclFunc (AstNode* current, LogHTML& log)
{
    int  typeVal = current[0]->key ().type;
    int  nameVal = current[1]->key ().value;
    int  argsVal = current[2]->size ();
    bool codeVal = (current->size () == 4);

    for (int i = func_.size () - 1; i >= 0; i--)
    {
        if (func_[i].name == nameVal &&
            func_[i].type == typeVal &&
            func_[i].args == argsVal)
        {
            if (func_[i].code == codeVal)
                LogError (log, "Function was declared before\n");

            if (codeVal) func_[i].code = true;

            //current[1]->key () = { Name, i };

            return;
        }
    }

    data_.push_back (-1);
    label_++;

    //current[1]->key () = { Name, func_.size () };
    func_.push_back ({ typeVal, nameVal, argsVal, codeVal });

    Detour (current[2], log);

    if (current->size () == 4)
    {
        for (int i = 0; i < current->children ()[3]->size (); i++)
            Detour (current->children ()[3]->children ()[i], log);
    }

    while (data_.back () != -1) data_.pop_back ();

    data_.pop_back ();
    label_--;
}

void CAP::SemanticAnalyzer::Check_Call (AstNode* current, LogHTML& log)
{
    int nameVal = current[0]->key ().value;
    int argsVal = current[1]->children ().size ();

    bool flag = false;
    for (int i = func_.size () - 1; i >= 0; i--)
    {
        if ((func_[i].name == nameVal) &&
            (func_[i].args == argsVal))
        {
            flag = true;

            break;
        }
    }

    //current->children ()[0]->key () = { Name, func_.size () };

    if (!flag)
        LogError (log, "Function wasn't declared before\n");
}

size_t CAP::SemanticAnalyzer::size ()
{
    return func_.size ();
}

#endif /* SemanticAnalyzer_hpp */
