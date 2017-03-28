#ifndef AbstractSyntaxNode_hpp

#define AbstractSyntaxNode_hpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <vector>
#include "..//Headers//FrontEnd//Token.hpp"
#include "..//Libraries//LogHTML.hpp"
#include "Dotter//Dotter.hpp"

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

#define Vector_t std::vector <AstNode*>

class AstNode
{
    private:
        //using Vector_t = std::vector <AstNode*>;

    public:
        AstNode ();
        AstNode (const Token& value);

        ~AstNode ();

        AstNode* operator [] (const size_t child) const;

        AstNode& insert ();
        AstNode& insert (const Token& value);
        AstNode& insert (const AstNode& example); //

        void erase ();

        bool empty () const;

        AstNode copy () const;
        AstNode& move (AstNode& from);

        void read (std::ifstream& in);
        void write (std::ofstream& out) const;

        bool ok   () const;
        void dump (std::ostream& out = std::cout) const;

		void render (Dotter::Digraph& tree, const size_t number, const bool information = false) const;

        Token& key ();
        size_t size ();
        Vector_t& children ();

        int& type ();
        int& value ();

    private:
        Token key_;

        Vector_t children_;

        AstNode (const AstNode& from); //

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

AstNode::AstNode (const AstNode& from): //
    key_      (from.key_),
    children_ (from.children_)
{
	//from.children_.clear ();

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

AstNode* AstNode::operator [] (const size_t child) const
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
        if (children_[i] == child)
            return (int) i;
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

AstNode& AstNode::insert (const AstNode& from) //
{
    OK_ASTNODE

    AstNode* example = new AstNode (from);

    children_.push_back (example);

    //from.clear ();

    OK_ASTNODE

    return (*this);
}

void AstNode::erase ()
{
    OK_ASTNODE

    clear ();

    OK_ASTNODE
}

bool AstNode::empty () const
{
    OK_ASTNODE

    return children_.empty ();
}

AstNode AstNode::copy () const
{
    OK_ASTNODE

    AstNode current (key_);

    for (size_t i = 0; i < children_.size (); i++)
        current.insert (children_[i]->copy ());

    OK_ASTNODE

    return current;
}

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
        children_[i] = from[i];
        //from[i] = nullptr;
    }

    from.children_.clear ();

    OK_ASTNODE

    return (*this);
}

void AstNode::read (std::ifstream& in)
{
    char comma = 0; // Needs for scan ','

    char start = 0;

    in >> start;

    assert (start == '<');

    in >> key_.type >> comma >> key_.value;

    for (char current = 0;;)
    {
        in >> current;

        if (current == '>')
            break;

        else if (current == ',')
        {
            in >> current;

            assert (current == '(');

            insert ();

            children_.back ()->read (in);

            in >> current;

            assert (current == ')');
        }

        else
            assert (false);
    }
}

void AstNode::write (std::ofstream& out) const
{
    out << "<";

    out << key_.type << "," << key_.value;

    if (!children_.empty ())
        out << ",";

    for (size_t i = 0; i < children_.size (); i++)
    {
        out << "(";

        children_[i]->write (out);

        out << ")";

        if (i != children_.size () - 1)
            out << ",";
    }

    out << ">";
}

bool AstNode::ok () const
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

void AstNode::dump (std::ostream& out /* = std::cout */) const
{
    out << "\n====================DUMP====================\n";

    out << "AstNode (" << (ok ()? "ok" : "ERROR") << "):\n";

    out << "\t[this = " << this << "];\n";
    out << "\t[key  = " << key_ << "];\n";
    out << "\t[size = " << children_.size () << "];\n";

    out << "============================================\n\n";
}

void AstNode::render (Dotter::Digraph& tree, const size_t number, const bool information /* = false */) const
{
	std::string title (BtInf (tree, key_));

    if (information)
    {
        char extra[640] = "";

        for (size_t i = 0; i < children_.size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, children_[i]);

        title += extra;
    }

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

Vector_t& AstNode::children ()
{
    OK_ASTNODE

    return children_;
}

int& AstNode::type ()
{
    return key_.type;
}

int& AstNode::value ()
{
    return key_.value;
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

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, const bool show);
void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t number);

bool operator == (const AstNode& a, const AstNode& b)
{
    return (&a == &b);
}

bool operator != (const AstNode& a, const AstNode& b)
{
    return !(&a == &b);
}

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, const bool show)
{
    const std::string path ("Libraries//Dotter");

    Dotter::Digraph tree;

    tree.dotter () = path;
    tree.text () = file_name;
    tree.photo () = render_name;

    tree.open ();

    root.render (tree, 0);

    for (size_t i = 0; i < root.size (); i++)
        RenderNode (tree, root.children ()[i], 0);

    tree.render (show);
}

void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t from)
{
    const size_t to = from + 1;

    current->render (tree, to);

    tree.link (from, to, "");

    for (size_t i = 0; i < current->size (); i++)
        RenderNode (tree, current[i], to);
}

#undef Vector_t

#endif /* AbstractSyntaxNode_hpp */
