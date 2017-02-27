#ifndef ASTNode_INCLUDED
    #define ASTNode_INCLUDED

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <vector>
#include "..//Headers//FrontEnd//Token.hpp"
#include "..//Libraries//LogHTML.hpp"

#define DEBUG_ASTNODE

#if defined (DEBUG_ASTNODE)

    #define DO_ASTNODE(codeDebug, codeTest)  codeDebug
    #define OK_ASTNODE ok ();

#elif defined (TEST_ASTNODE)

    #define DO_ASTNODE(codeDebug, codeTest)  codeTest
    #define OK_ASTNODE assert (ok ());

#elif defined (RELEASE_ASTNODE)

    #define DO_ASTNODE(codeDebug, codeTest)
    #define OK_ASTNODE

#else

    #error "Either DEBUG_ASTNODE or TEST_ASTNODE or RELEASE_ASTNODE MUST be defined"

#endif

class AstNode
{
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

        bool ok   ();
        void dump (FILE* out = stdout);

		void render (Dotter::Digraph& tree, const size_t number);

        Token&                  key ();
        size_t                 size ();
        std::vector <AstNode*>& children ();

    private:
        Token key_;

        std::vector <AstNode*> children_;

        AstNode (AstNode& from);

        AstNode& operator =  (AstNode& from);

        int position (AstNode* child);

        void clear ();
};

AstNode::AstNode ():
    key_      (),
    children_ ()
{ 
	OK_ASTNODE 
}

AstNode::AstNode (const Token& value):
    key_      (value),
    children_ ()
{ 
	OK_ASTNODE 
}

AstNode::AstNode (AstNode& from):
    key_      (from.key_),
    children_ (from.children_)
{
	from.children_.clear ();

    OK_ASTNODE
}

AstNode::~AstNode ()
{
    OK_ASTNODE

    clear ();

    OK_ASTNODE
}

AstNode& AstNode::operator = (AstNode& from)
{
    OK_ASTNODE

    key_      = from.key_;
    children_ = from.children_;

    from.children_.clear ();

    OK_ASTNODE

    return (*this);
}

AstNode* AstNode::operator [] (const size_t child)
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

int AstNode::position (AstNode* child)
{
    OK_ASTNODE

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i] == child) return (int) i;
    }

    OK_ASTNODE

    return -1;
}

AstNode& AstNode::insert  ()
{
    OK_ASTNODE

    AstNode from;

    OK_ASTNODE

    return insert (from);
}

AstNode& AstNode::insert (const Token& value)
{
    OK_ASTNODE

    AstNode from (value);

    OK_ASTNODE

    return insert (from);
}

AstNode& AstNode::insert (AstNode& from)
{
    OK_ASTNODE

    AstNode* example = new AstNode (from);

    children_.push_back (example);

    from.clear ();

    OK_ASTNODE

    return (*this);
}

void AstNode::erase ()
{
    OK_ASTNODE

    clear ();

    OK_ASTNODE
}

bool AstNode::empty ()
{
    OK_ASTNODE

    return children_.empty ();
}

/*AstNode& AstNode::copy (const AstNode& from)
{
    OK_ASTNODE

    AstNode current (from.key_);

    for (size_t i = 0; i < from.children_.size (); i++) current.insert (copy (children_[i]));

    OK_ASTNODE

    return current;
}*/

AstNode& AstNode::move (AstNode& from)
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

void AstNode::read (FILE* out)
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

void AstNode::write (FILE* in)
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

bool AstNode::ok ()
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

void AstNode::dump (FILE* out /* = stdout */)
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

void AstNode::render (Dotter::Digraph& tree, const size_t number)
{
	std::string title (BtInf (tree, key_));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < children_.size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, children_[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    tree.node (number, title.c_str ());
}

Token& AstNode::key ()
{
    OK_ASTNODE

    return key_;
}

size_t AstNode::size ()
{
    OK_ASTNODE

    return children_.size ();
}

std::vector <AstNode*>& AstNode::children ()
{
    OK_ASTNODE

    return children_;
}

void AstNode::clear ()
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

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, bool show);
void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t number);

bool operator == (const AstNode& a, const AstNode& b)
{
    return (&a == &b);
}

bool operator != (const AstNode& a, const AstNode& b)
{
    return !(&a == &b);
}

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, bool show)
{
    Dotter::Digraph tree (file_name.c_str (), render_name.c_str ());

    tree.open ();

    root.render (tree, 0);

    for (size_t i = 0; i < root.children ().size (); i++)
        RenderNode (tree, root.children ()[i], 0);

    tree.render ("Libraries//Dotter", show);
}

void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t number)
{
    static size_t count = 0;
                  count++;

    current->render (tree, count);

    tree.link (number, count, "");

    size_t copy_count = count;

    for (size_t i = 0; i < current -> children ().size (); i++)
        RenderNode (tree, current -> children ()[i], copy_count);
}

#endif
