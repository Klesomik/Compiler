#ifndef DeerLib_hpp
    #define DeerLib_hpp

//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "..//Librarys//AbstractSyntaxNode.hpp"
#include "..//Librarys//LogHTML.hpp"
#include "..//Librarys//Dotter//Dotter.h"
#include "Token.hpp"

//}==============================================================================

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

void RenderTree (AstNode& root, const string& file_name)
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
    #define DEER_EXTRA(id, name, word, fontcolor, color, fillcolor, shape, style) \
    case id:\
    {\
        SetStyle (shape, style);\
        SetColor (fontcolor, color, fillcolor);\
    \
        return string (word);\
    }

    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style) \
    case id:\
    {\
        SetStyle (shape, style);\
        SetColor (fontcolor, color, fillcolor);\
    \
        return string (word);\
    }

    switch (value.type)
    {
        #include "CList.hpp"

        default: { throw "BtInf was broken"; }
    }

    #undef DEER_EXTRA

    #undef DEER
}

#endif
