#ifndef ASTNode_INCLUDED
    #define ASTNode_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include "..//Headers//FrontEnd//Token.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define DEBUG_ASTNODE

#if defined (DEBUG_ASTNODE)

    #include "Debug.hpp"
    #define DO_ASTNODE(codeDebug, codeTest)  codeDebug
    #define OK_ASTNODE ok ();

#elif defined (TEST_ASTNODE)

    #include "Debug.hpp"
    #define DO_ASTNODE(codeDebug, codeTest)  codeTest
    #define OK_ASTNODE assert (ok ());

#elif defined (RELEASE_ASTNODE)

    #define DO_ASTNODE(codeDebug, codeTest)
    #define OK_ASTNODE

#else

    #error "Either DEBUG_ASTNODE or TEST_ASTNODE or RELEASE_ASTNODE MUST be defined"

#endif

//}==============================================================================

//Class: AstNode
//{==============================================================================

class AstNode
{
    private:
        Token key_;

        AstNode* parent_;

        std::vector <AstNode*> children_;

        AstNode (AstNode& from);

        AstNode& operator =  (AstNode& from);

        int position (AstNode* child);

    public:
        AstNode ();
        AstNode (const Token& value);

        ~AstNode ();

        AstNode* operator [] (const size_t child);

        AstNode& insert ();
        AstNode& insert (const Token& value);
        AstNode& insert (AstNode& example);

        void erase ();

        AstNode& copy (const AstNode& from);
        AstNode& move (AstNode& from);

        Token&                  key ();
        size_t                 size ();
        AstNode*             parent ();
        std::vector <AstNode*>& children ();

        bool ok   ();
        void dump (FILE* out = stdout);
};

//}==============================================================================

AstNode :: AstNode ():
    key_      (),
    parent_   (nullptr),
    children_ ()
    { OK_ASTNODE }

//===============================================================================

AstNode :: AstNode (const Token& value):
    key_      (value),
    parent_   (nullptr),
    children_ ()
    { OK_ASTNODE }

//===============================================================================

AstNode :: AstNode (AstNode& from):
    key_      (from.key_),
    parent_   (from.parent_),
    children_ (from.children_)
    {
        from.parent_ = nullptr;

        from.children_.clear ();

        for (size_t i = 0; i < children_.size (); i++)  children_[i] -> parent_ = this;

        OK_ASTNODE
    }

//===============================================================================

AstNode :: ~AstNode ()
{
    OK_ASTNODE

    if (parent_) parent_ = nullptr;

    for (size_t i = 0; i < children_.size (); i++)
    {
        delete children_[i];
               children_[i] = nullptr;
               children_.erase (children_.begin () + i);
    }

    children_.resize (0);
    children_.clear ();

    OK_ASTNODE
}

//===============================================================================

AstNode& AstNode :: operator = (AstNode& from)
{
    OK_ASTNODE

    key_      = from.key_;
    parent_   = from.parent_;
    children_ = from.children_;

    from.parent_ = nullptr;
    from.children_.clear ();

    for (size_t i = 0; i < children_.size (); i++)  children_[i] -> parent_ = this;

    OK_ASTNODE

    return (*this);
}

//===============================================================================

AstNode* AstNode :: operator [] (const size_t child)
{
    OK_ASTNODE

    if (child >= children_.size ())
    {
        DO_ASTNODE ({ throw "Not found this children"; },
                    { assert (false); })
    }

    OK_ASTNODE

    return children_[child];
}

//===============================================================================

int AstNode :: position (AstNode* child)
{
    OK_ASTNODE

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i] == child) return i;
    }

    OK_ASTNODE

    return -1;
}

//===============================================================================

AstNode& AstNode :: insert  ()
{
    OK_ASTNODE

    AstNode from;

    OK_ASTNODE

    return insert (from);
}

//===============================================================================

AstNode& AstNode :: insert (const Token& value)
{
    OK_ASTNODE

    AstNode from (value);

    OK_ASTNODE

    return insert (from);
}

//===============================================================================

AstNode& AstNode :: insert (AstNode& from)
{
    OK_ASTNODE

    AstNode* example = new AstNode (from);

    children_.push_back (example);
                         example -> parent_ = this;

    from.~AstNode ();

    OK_ASTNODE

    return (*this);
}

//===============================================================================

void AstNode :: erase ()
{
    OK_ASTNODE

    int i = parent_ -> position (this);

    parent_ -> children ().erase (parent_ -> children ().begin () + i);

    parent_ = nullptr;

    this -> ~AstNode ();

    OK_ASTNODE
}

//===============================================================================

/*AstNode& AstNode :: copy (const AstNode& from)
{
    OK_ASTNODE

    AstNode current (from.key_);

    for (size_t i = 0; i < from.children_.size (); i++) current.insert (copy (children_[i]));

    OK_ASTNODE

    return current;
}*/

//===============================================================================

AstNode& AstNode :: move (AstNode& from)
{
    OK_ASTNODE

    if (parent_)
    {
        DO_ASTNODE ({ throw "parent_"; },
                    { assert (false);  })
    }

    for (size_t i = 0; i < children_.size (); i++)
    {
        delete children_[i];
               children_[i] = nullptr;
    }

    children_.resize (from.children_.size ());

    key_ = from.key_;

    for (size_t i = 0; i < children_.size (); i++)
    {
        children_[i] = from.children_[i];
        children_[i] -> parent_ = this;
        from.children_[i] = nullptr;
    }

    from.children_.clear ();

    OK_ASTNODE

    return (*this);
}

//===============================================================================

bool AstNode :: ok ()
{
    if (parent_)
    {
        int number = parent_ -> position (this);

        if (number == -1)
        {
            DO_ASTNODE ({ throw "parent_ -> left_ != this && parent_ -> right_ != this"; },
                        { return false; })
        }
    }

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i] -> parent_ != this)
        {
            DO_ASTNODE ({ throw "children_[i] -> parent_ != this"; },
                        { return false; })
        }
    }

    return true;
}

//===============================================================================

void AstNode :: dump (FILE* out /* = stdout */)
{
    fprintf (out, "\n====================DUMP====================\n");

    fprintf (out, "AstNode (%s) [this = %p]", ok()? "ok" : "ERROR", this);

    std::cout << "[" << key_ << "];\n";

    fprintf (out, "    parent = [%p];\n", parent_);

    for (size_t i = 0; i < children_.size (); i++)
    {
        fprintf (out, "    child[%d] = [%p]", i, children_[i]);
        std::cout << "[" << children_[i] -> key () << "]\n";
    }

    fprintf (out, "============================================\n\n");
}

//===============================================================================

Token& AstNode :: key ()
{
    OK_ASTNODE

    return key_;
}

//===============================================================================

size_t AstNode :: size ()
{
    OK_ASTNODE

    return children_.size ();
}

//===============================================================================

AstNode* AstNode :: parent ()
{
    OK_ASTNODE

    return parent_;
}

//===============================================================================

std::vector <AstNode*>& AstNode :: children ()
{
    OK_ASTNODE

    return children_;
}

bool operator == (const AstNode& a, const AstNode& b);
bool operator != (const AstNode& a, const AstNode& b);

bool operator == (const AstNode& a, const AstNode& b)
{
    return (&a == &b);
}

bool operator != (const AstNode& a, const AstNode& b)
{
    return !(&a == &b);
}

#include "AstNodeLib.hpp"

#endif
