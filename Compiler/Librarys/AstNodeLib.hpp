#ifndef ASTNodeLIB_INCLUDED
    #define ASTNodeLIB_INCLUDED

//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Dotter//Dotter.h"
#include "..//Headers//FrontEnd//LexicialAnalyzer.hpp"

//}==============================================================================

using namespace std;

//{==============================================================================

void DotDump  (AstNode& root, const string& file_name);
void GrowTree (AstNode* current, const size_t number);
string BtInf (const Token value);

//}==============================================================================

void DotDump (AstNode& root, const string& file_name)
{
    dtBegin (file_name.c_str ());

    dtNodeStyle ().shape ("box")
                  .style ("rounded, filled");

    string title (BtInf (root.key ()));

    #ifdef TEST_ASTNODE

        char extra[640] = "";

        for (size_t i = 0; i < root.children ().size (); i++)
            sprintf (extra, "child[%d] = %p\n", i, root.children ()[i]);

        title += extra;

    #endif /* DEBUG_ASTNODE */

    dtNode (0, title.c_str ());

    for (size_t i = 0; i < root.children ().size (); i++)
        GrowTree (root.children ()[i], 0);

    dtEnd ();

    dtRender (file_name.c_str ());
}

void GrowTree (AstNode* current, const size_t number)
{
    static size_t count = 0;
                  count++;

    string title (BtInf (current -> key ()));

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
        GrowTree (current -> children ()[i], copy_count);
}

string BtInf (const Token value)
{
    char tmp[5] = "";

    if (value.type == Digit)
    {
        dtNodeStyle ().fontcolor ("darkgreen")
                      .color     ("darkgreen")
                      .fillcolor ("#98FF66");

        sprintf (tmp, "%d\n", value.value);
    }

    else if (value.type == Var)
    {
        dtNodeStyle ().fontcolor ("darkgreen")
                      .color     ("darkgreen")
                      .fillcolor ("#98FF66");

        sprintf (tmp, "var_%d\n", value.value);
    }

    else if (value.type == If)
    {
        dtNodeStyle ().fontcolor ("blue")
                      .color     ("blue")
                      .fillcolor ("lightblue");

        sprintf (tmp, "if\n");
    }

    else if (value.type == None)
    {
        dtNodeStyle ().fontcolor ("grey")
                      .color     ("grey")
                      .fillcolor ("grey");

        sprintf (tmp, "If\n");
    }

    else
    {
        dtNodeStyle ().fontcolor ("red")
                      .color     ("red")
                      .fillcolor ("#FFCCC9");

        switch (value.type)
        {
            case Add:        { sprintf (tmp, "+\n");  break; }
            case Sub:        { sprintf (tmp, "-\n");  break; }
            case Mul:        { sprintf (tmp, "*\n");  break; }
            case Div:        { sprintf (tmp, "/\n");  break; }
            case Assignment: { sprintf (tmp, "=\n");  break; }
            case Equal:      { sprintf (tmp, "==\n"); break; }

            default: break;
        }
    }

    return string (tmp);
}

#endif
