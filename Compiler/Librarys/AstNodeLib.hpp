#ifndef ASTNodeLIB_INCLUDED
    #define ASTNodeLIB_INCLUDED

//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Dotter.h"

//}==============================================================================

using namespace std;

//{==============================================================================

void SetColor (const char* first, const char* second, const char* third);
void DotDump  (AstNode& root, const string& file_name);
void GrowTree (AstNode* current, const size_t number);
string BtInf (const Token value);

//}==============================================================================

void SetColor (const char* first, const char* second, const char* third)
{
    dtNodeStyle ().fontcolor (first)
                  .color     (second)
                  .fillcolor (third);
}

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

    if (value.type == Digit ||
        value.type == Var)
    {
        SetColor ("darkgreen", "darkgreen", "#98FF66");

        switch (value.type)
        {
            case Digit: { sprintf (tmp, "%d\n", value.value); break; }
            case   Var: { sprintf (tmp, "var_%d\n", value.value); break; }

            default: break;
        }
    }

    else if (value.type == If    ||
             value.type == While ||
             value.type == Int)
    {
        SetColor ("blue", "blue", "lightblue");

        switch (value.type)
        {
            case    If: { sprintf (tmp, "if\n");    break; }
            case While: { sprintf (tmp, "while\n"); break; }
            case   Int: { sprintf (tmp, "int\n");   break; }

            default: break;
        }
    }

    else if (value.type == None ||
             value.type == Declaration)
    {
        SetColor ("grey", "grey", "lightgrey");
    }

    else if (value.type == Add        ||
             value.type == Sub        ||
             value.type == Mul        ||
             value.type == Div        ||
             value.type == Mod        ||
             value.type == Assignment ||
             value.type == Equal      ||
             value.type == NotEqual   ||
             value.type == And        ||
             value.type == Or         ||
             value.type == Less       ||
             value.type == More       ||
             value.type == LessEqual  ||
             value.type == MoreEqual)
    {
        SetColor ("red", "red", "#FFCCC9");

        switch (value.type)
        {
            case        Add: { sprintf (tmp, "+\n");        break; }
            case        Sub: { sprintf (tmp, "-\n");        break; }
            case        Mul: { sprintf (tmp, "*\n");        break; }
            case        Div: { sprintf (tmp, "/\n");        break; }
            case        Mod: { sprintf (tmp, "%c\n", '%');  break; }
            case Assignment: { sprintf (tmp, "=\n");        break; }
            case      Equal: { sprintf (tmp, "==\n");       break; }
            case   NotEqual: { sprintf (tmp, "!=\n");       break; }
            case        And: { sprintf (tmp, "&&\n");       break; }
            case         Or: { sprintf (tmp, "||\n");       break; }
            case       Less: { sprintf (tmp, "<\n");        break; }
            case       More: { sprintf (tmp, ">\n");        break; }
            case  LessEqual: { sprintf (tmp, "<=\n");       break; }
            case  MoreEqual: { sprintf (tmp, ">=\n");       break; }

            default: break;
        }
    }

    return string (tmp);
}

#endif
