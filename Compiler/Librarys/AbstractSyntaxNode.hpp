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
#include "..//Librarys//LogHTML.hpp"
#include "C:\Users\Artem\Desktop\DotterOld\Dotter.h"

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

        AstNode* parent_;

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

    clear ();

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
                         example -> parent_ = this;

    from.clear ();

    OK_ASTNODE

    return (*this);
}

//===============================================================================

void AstNode :: erase ()
{
    OK_ASTNODE

    if (parent_)
    {
        int i = parent_ -> position (this);

        parent_ -> children ().erase (parent_ -> children ().begin () + i);

        parent_ = nullptr;
    }

    clear ();

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

//===============================================================================

void AstNode :: clear ()
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

//{==============================================================================

void SetStyle (const char* first, const char* second);
void SetColor (const char* first, const char* second, const char* third);

void RenderTree (AstNode&    root, const std::string& file_name);
void RenderNode (AstNode* current, const size_t number);

std::string BtInf (const Token& value);

//}==============================================================================

void SetStyle (const char* first, const char* second)
{
    dtNodeStyle ().shape (first)
                  .style (second);
}

//===============================================================================

void SetColor (const char* first, const char* second, const char* third)
{
    dtNodeStyle ().fontcolor (first)
                  .color     (second)
                  .fillcolor (third);
}

//===============================================================================

void RenderTree (AstNode& root, const std::string& file_name)
{
    dtBegin (file_name.c_str ());

    std::string title (BtInf (root.key ()));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < root.children ().size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, root.children ()[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    dtNode (0, title.c_str ());

    for (size_t i = 0; i < root.children ().size (); i++)
        RenderNode (root.children ()[i], 0);

    dtEnd ();

    dtRender (file_name.c_str ());
}

//===============================================================================

void RenderNode (AstNode* current, const size_t number)
{
    static size_t count = 0;
                  count++;

    std::string title (BtInf (current -> key ()));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < current -> children ().size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, current -> children ()[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    dtNode (count, title.c_str ());
    dtLink (number, count);

    size_t copy_count = count;

    for (size_t i = 0; i < current -> children ().size (); i++)
        RenderNode (current -> children ()[i], copy_count);
}

//===============================================================================

std::string BtInf (const Token& value)
{
    #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (shape, style);\
        SetColor (fontcolor, color, fillcolor);\
    \
        return std::string (word);\
    }

    #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (shape, style);\
        SetColor (fontcolor, color, fillcolor);\
    \
        return std::string (word);\
    }

    #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (shape, style);\
        SetColor (fontcolor, color, fillcolor);\
    \
        return std::string (word);\
    }

    switch (value.type)
    {
        #include "..//Headers//FrontEnd//CList.hpp"

        default: { throw "BtInf was broken"; }
    }

    #undef DEER_0
    #undef DEER_1
    #undef DEER_2
}

#endif
