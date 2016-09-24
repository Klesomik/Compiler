#ifndef ASTInfo_INCLUDED
    #define ASTInfo_INCLUDED

#include <cstdio>
#include <iostream>
#include "Dotter//Dotter.hpp"
#include "..//Headers//FrontEnd//Token.hpp"

//{==============================================================================

void SetStyle (Dotter::Digraph& tree, const char* first, const char* second);
void SetColor (Dotter::Digraph& tree, const char* first, const char* second, const char* third);

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name);
void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t number);

std::string BtInf (Dotter::Digraph& tree, const Token& value);

//}==============================================================================

void SetStyle (Dotter::Digraph& tree, const char* first, const char* second)
{
    tree.set ("shape", first);
    tree.set ("style", second);
}

//===============================================================================

void SetColor (Dotter::Digraph& tree, const char* first, const char* second, const char* third)
{
    tree.set ("fontcolor", first);
    tree.set ("color", second);
    tree.set ("fillcolor", third);
}

//===============================================================================

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name)
{
    Dotter::Digraph tree (file_name.c_str (), render_name.c_str ());

    tree.open ();

    std::string title (BtInf (tree, root.key ()));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < root.children ().size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, root.children ()[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    tree.node (0, title.c_str ());

    for (size_t i = 0; i < root.children ().size (); i++)
        RenderNode (tree, root.children ()[i], 0);

    tree.render ("Libraries//Dotter");
}

//===============================================================================

void RenderNode (Dotter::Digraph& tree, AstNode* current, const size_t number)
{
    static size_t count = 0;
                  count++;

    std::string title (BtInf (tree, current -> key ()));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < current -> children ().size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, current -> children ()[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    tree.node (count, title.c_str ());
    tree.link (number, count, "");

    size_t copy_count = count;

    for (size_t i = 0; i < current -> children ().size (); i++)
        RenderNode (tree, current -> children ()[i], copy_count);
}

//===============================================================================

std::string BtInf (Dotter::Digraph& tree, const Token& value)
{
    #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (tree, shape, style);\
        SetColor (tree, fontcolor, color, fillcolor);\
    \
        return std::string (word);\
    }

    #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (tree, shape, style);\
        SetColor (tree, fontcolor, color, fillcolor);\
    \
        return std::string (word);\
    }

    #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id:\
    {\
        SetStyle (tree, shape, style);\
        SetColor (tree, fontcolor, color, fillcolor);\
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
