#ifndef ASTInfo_INCLUDED
    #define ASTInfo_INCLUDED

#include <cstdio>
#include <iostream>
#include "Dotter//Dotter.hpp"
#include "..//Headers//FrontEnd//Token.hpp"

std::map <int, std::vector <std::string>> colors = { {        Digit, { "darkgreen", "darkgreen",   "#98FF66",     "box", "rounded, filled" } },
                                                     {         Name, { "darkgreen", "darkgreen",   "#98FF66",     "box", "rounded, filled" } },
                                                     {        Block, {     "black",     "black", "lightgrey", "ellipse", "rounded, filled" } },
                                                     {      DeclVar, {     "black",     "black", "lightgrey", "ellipse", "rounded, filled" } },
                                                     {     DeclFunc, {     "black",     "black", "lightgrey", "ellipse", "rounded, filled" } },
                                                     {         Call, {     "black",     "black", "lightgrey", "ellipse", "rounded, filled" } },
                                                     {       Params, {     "black",     "black", "lightgrey", "ellipse", "rounded, filled" } },
                                                     {        Equal, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     NotEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          And, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {           Or, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Not, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {    LessEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {    MoreEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Mul, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Div, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Mod, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Add, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {          Sub, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {   Assingment, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {         Less, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {         More, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {       BitAnd, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {        BitOr, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {       BitXor, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {       BitNot, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {    ShiftLeft, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {   ShiftRight, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     AddEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     SubEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     MulEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     DivEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     ModEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     AndEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {      OrEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {     XorEqual, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {    Increment, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {    Decrement, {       "red",       "red",   "#FFCCC9",     "box", "rounded, filled" } },
                                                     {           If, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {        While, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {          Int, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {         Void, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {       Return, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {        Break, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {          Out, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } },
                                                     {     Continue, {      "blue",      "blue", "lightblue",     "box", "rounded, filled" } } };

//{==============================================================================

void SetStyle (Dotter::Digraph& tree, const char* first, const char* second);
void SetColor (Dotter::Digraph& tree, const char* first, const char* second, const char* third);

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, bool show);
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

void RenderTree (AstNode& root, const std::string& file_name, const std::string& render_name, bool show)
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

    tree.render ("Libraries//Dotter", show);
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
    #define DEER(id, name, word, code) \
    case id:\
    {\
        SetStyle (tree, colors[name][3].c_str (), colors[name][4].c_str ());\
        SetColor (tree, colors[name][0].c_str (), colors[name][1].c_str (), colors[name][2].c_str ());\
    \
        return std::string (word);\
    }

    switch (value.type)
    {
        #include "..//Headers//FrontEnd//CList.inl"

        default: { throw "BtInf was broken"; }
    }

    #undef DEER
}

#endif
