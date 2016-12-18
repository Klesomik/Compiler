#ifndef ASTNode_INCLUDED
    #define ASTNode_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <vector>
#include "..//Headers//FrontEnd//Token.hpp"
#include "..//Libraries//LogHTML.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define DEBUG_ASTNODE

#if defined (DEBUG_ASTNODE)

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

        std::vector <AstNode*> children_;

        AstNode (AstNode& from);

        AstNode& operator =  (AstNode& from);

        int position (AstNode* child);

        void clear ();

    public:
        AstNode ();
        AstNode (const Token& value);

        ~AstNode ();

        AstNode* operator [] (const size_t child);

        AstNode& insert ();
        AstNode& insert (const Token& value);
        AstNode& insert (AstNode& example);

        void erase ();

        bool empty ();

        AstNode& copy (const AstNode& from);
        AstNode& move (AstNode& from);

        void read (FILE* out);
        void write (FILE* in);

        Token&                  key ();
        size_t                 size ();
        std::vector <AstNode*>& children ();

        bool ok   ();
        void dump (FILE* out = stdout);
};

//}==============================================================================

AstNode :: AstNode ():
    key_      (),
    children_ ()
    { OK_ASTNODE }

//===============================================================================

AstNode :: AstNode (const Token& value):
    key_      (value),
    children_ ()
    { OK_ASTNODE }

//===============================================================================

AstNode :: AstNode (AstNode& from):
    key_      (from.key_),
    children_ (from.children_)
    {
        from.children_.clear ();

        OK_ASTNODE
    }

//===============================================================================

AstNode :: ~AstNode ()
{
    OK_ASTNODE

    clear ();

    OK_ASTNODE
}

//===============================================================================

AstNode& AstNode :: operator = (AstNode& from)
{
    OK_ASTNODE

    key_      = from.key_;
    children_ = from.children_;

    from.children_.clear ();

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
        if (children_[i] == child) return (int) i;
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

    from.clear ();

    OK_ASTNODE

    return (*this);
}

//===============================================================================

void AstNode :: erase ()
{
    OK_ASTNODE

    clear ();

    OK_ASTNODE
}

//===============================================================================

bool AstNode :: empty ()
{
    OK_ASTNODE

    return children_.empty ();
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
        from.children_[i] = nullptr;
    }

    from.children_.clear ();

    OK_ASTNODE

    return (*this);
}

//===============================================================================

void AstNode :: read (FILE* out)
{
    char start = 0;

    fscanf (out, "%c", &start);

    assert (start == '<');

    fscanf (out, "%d,%d", &key_.type, &key_.value);

    for (char current = 0;;)
    {
        fscanf (out, "%c", &current);

        if (current == '>') break;

        else if (current == ',')
        {
            fscanf (out, "%c", &current);

            assert (current == '(');

            insert ();

            children_[children_.size () - 1] -> read (out);

            fscanf (out, "%c", &current);

            assert (current == ')');
        }

        else assert (false);
    }
}

//===============================================================================

void AstNode :: write (FILE* in)
{
    fprintf (in, "<");

    fprintf (in, "%d,%d", key_.type, key_.value);

    if (!children_.empty ())
        fprintf (in, ",");

    for (size_t i = 0; i < children_.size (); i++)
    {
        fprintf (in, "(");

        children_[i] -> write (in);

        fprintf (in, ")");

        if (i != children_.size () - 1)
            fprintf (in, ",");
    }

    fprintf (in, ">");
}

//===============================================================================

bool AstNode :: ok ()
{
    for (size_t i = 0; i < children_.size (); i++)
    {
        if (!children_[i])
        {
            DO_ASTNODE ({ throw "!children_[i]"; },
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

    for (size_t i = 0; i < children_.size (); i++)
    {
        fprintf (out, "    child[%zu] = [%p]", i, children_[i]);
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

std::vector <AstNode*>& AstNode :: children ()
{
    OK_ASTNODE

    return children_;
}

//===============================================================================

void AstNode :: clear ()
{
    OK_ASTNODE

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

#include "ASTInfo.hpp"

#endif
