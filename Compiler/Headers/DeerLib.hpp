#ifndef DeerLib_hpp
    #define DeerLib_hpp

//{==============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "AstNodeLib.hpp"
#include "..//Librarys//LogHTML.hpp"
#include "Dotter.h"

//}==============================================================================

//{==============================================================================

void SetColor (const char* first, const char* second, const char* third);
void DotDump  (AstNode& root, const std::string& file_name);
void GrowTree (AstNode* current, const size_t number);
std::string BtInf (const Token value);

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

    std::string title (BtInf (root.key ()));

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
        GrowTree (current -> children ()[i], copy_count);
}

std::string BtInf (const Token value)
{
    char tmp[5] = "";

    #define DEER(id, name, word, dot_color)         case id: { word                       break; }
    #define DEER_DEFAULT(id, name, word, dot_color) case id: { sprintf (tmp, "%s", word); break; }

    switch (value.type)
    {
        #include "CList.hpp"

        default: { break; }
    }

    return string (tmp);
}

//{==============================================================================

template <typename Data_T>
bool check (Stream <Data_T>& example);

template <typename Data_T>
size_t avaliable (Stream <Data_T>& example);

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const std::initializer_list <Data_T>& next);

template <typename Data_T>
bool compare (Stream <Data_T>& example, const Data_T& element, const size_t shift);

//}==============================================================================

//===============================================================================

template <typename Data_T>
bool check (Stream <Data_T>& example)
{
    return (example.place () < example.size ());
}

//===============================================================================

template <typename Data_T>
size_t avaliable (Stream <Data_T>& example)
{
    return (example.size () - example.place ());
}

//===============================================================================

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const std::initializer_list <Data_T>& next)
{
    return check_next (next.begin (), next.size ());
}

//===============================================================================

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const Data_T next[], const size_t len)
{
    if (avaliable (example) < len) return false;

    for (size_t i = 0; i < len; i++)
    {
        if (example[example.place () + i] != next[i]) return false;
    }

    return true;
}

//===============================================================================

template <typename Data_T>
bool compare (Stream <Data_T>& example, const Data_T& element, const size_t shift)
{
    if (shift < avaliable (example)) return false;

    if (example[example.place () + shift] != element) return false;

    return true;
}

#endif
