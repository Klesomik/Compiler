#include <cstdio>
#include <cstring>
#include <iostream>
#include "..//Headers//FrontEnd//LexicialAnalyzer.hpp"

using namespace std;

void Check (const char* message);

BinaryNode <Token>& Read (FILE* scan);

void Write     (BinaryNode <Token>&    root, FILE* print);
void WriteTree (BinaryNode <Token>* current, FILE* print);

template <typename Data_T>
void DotDump  (BinaryNode <Data_T>& root, const string& file_name);

template <typename Data_T>
void GrowTree (BinaryNode <Data_T>* current, const size_t number);

template <typename Data_T>
BinaryNode <Data_T>& GetFirst (BinaryNode <Data_T>* example);

template <typename Data_T>
BinaryNode <Data_T>& Convert (BinaryNode <Data_T>* example);

string BtInf (const int    value, bool dot = false);
string BtInf (const char   value, bool dot = false);
string BtInf (const float  value, bool dot = false);
string BtInf (const double value, bool dot = false);
string BtInf (const string value, bool dot = false);
string BtInf (const Token  value, bool dot);

void Check (const char* message)
{
    #ifdef DEBUG_BINARYNODE

        throw message;

    #endif /* DEBUG_BINARYNODE */

    #ifdef TEST_BINARYNODE

    #endif /* TEST_BINARYNODE */
}

BinaryNode <Token>& Read (FILE* scan)
{
    static BinaryNode <Token> poison ({ -0xBADBEEF, -0xBADBEEF });

    char sym = -1;
    if ((fscanf (scan, "%c", &sym) != 1) || (sym != '(' && sym != '*'))
    {
        Check ("Syntax error 1\n");

        return poison;
    }

    if (sym == '*') return poison;

    int type = 0, value = 0;
    if (fscanf (scan, " <%d %d>", &type, &value) != 2)
    {
        Check ("Syntax error 2\n");

        return poison;
    }

    Token tmp (type, value);

    BinaryNode <Token> current (tmp);

    BinaryNode <Token> left;
                       left.move (Read (scan));
    BinaryNode <Token> right;
                       right.move (Read (scan));

    if (left.key  ().type_ != -0xBADBEEF) current.insertLeft   (left);
    if (right.key ().type_ != -0xBADBEEF) current.insertRight (right);

    if (fscanf (scan, " %c", &sym) != 1 || sym != ')')
    {
        Check ("Syntax error 3\n");

        return poison;
    }

    return current;
}

void Write (BinaryNode <Token>& root, FILE* print)
{
    fprintf (print, "(");

    string title (BtInf (root.key (), false));

    fprintf (print, "<%s>", title.c_str ());

    WriteTree (root.left  (), print);
    WriteTree (root.right (), print);

    fprintf (print, ")");
}

void WriteTree (BinaryNode <Token>* current, FILE* print)
{
    if (!current)
    {
        fprintf (print, "*");

        return;
    }

    fprintf (print, "(");

    string title (BtInf (current -> key (), false));

    fprintf (print, "<%s>", title.c_str ());

    WriteTree (current -> left  (), print);
    WriteTree (current -> right (), print);

    fprintf (print, ")");
}

template <typename Data_T>
void DotDump (BinaryNode <Data_T>& root, const string& file_name)
{
    dtBegin (file_name.c_str ());

    dtNodeStyle ().shape ("box")
                  .style ("rounded, filled");

    string title (BtInf (root.key (), true));

    /*#ifdef DEBUG_BINARYNODE

        char extra[640] = "";

        sprintf (extra, "parent = %p\n", root.parent ());
        sprintf (extra, "left   = %p\n", root.left   ());
        sprintf (extra, "right  = %p\n", root.right  ());

        title += extra;

    #endif /* DEBUG_BINARYNODE */

    dtNode (0, title.c_str ());

    GrowTree (root.left  (), 0);
    GrowTree (root.right (), 0);

    dtEnd ();

    dtRender (file_name.c_str ());
}

template <typename Data_T>
void GrowTree (BinaryNode <Data_T>* current, const size_t number)
{
    static size_t count = 0;
                  count++;

    string title (BtInf (current -> key (), true));

    /*#ifdef DEBUG_BINARYNODE

        char extra[640] = "";

        sprintf (extra, "parent = %p\n", current -> parent ());
        sprintf (extra, "left   = %p\n", current -> left   ());
        sprintf (extra, "right  = %p\n", current -> right  ());

        title += extra;

    #endif /* DEBUG_BINARYNODE */

    dtNode (count, title.c_str ());
    dtLink (number, count);

    size_t copy_count = count;

    if (current -> left  ()) GrowTree (current -> left  (), copy_count);
    if (current -> right ()) GrowTree (current -> right (), copy_count);
}

template <typename Data_T>
BinaryNode <Data_T>& GetFirst (BinaryNode <Data_T>* example)
{
    while (example -> parent ()) example = example -> parent ();

    return example;
}

string BtInf (const int value, bool dot /* = false */)
{
    char tmp[5] = "";
    sprintf (tmp, "%d", value);

    return string (tmp);
}

string BtInf (const char value, bool dot /* = false */)
{
    char tmp[5] = "";
    sprintf (tmp, "%c", value);

    return string (tmp);
}

string BtInf (const float value, bool dot /* = false */)
{
    char tmp[5] = "";
    sprintf (tmp, "%f", value);

    return string (tmp);
}

string BtInf (const double value, bool dot /* = false */)
{
    char tmp[5] = "";
    sprintf (tmp, "%lg", value);

    return string (tmp);
}

string BtInf (const string value, bool dot /* = false */)
{
    char tmp[5] = "";
    sprintf (tmp, "%s", value.c_str ());

    return string (tmp);
}

string BtInf (const Token value, bool dot /* = false */)
{
    char tmp[5] = "";

    if (dot)
    {
        if (value.type_ == 0)
        {
            dtNodeStyle ().fontcolor ("darkgreen")
                          .color     ("darkgreen")
                          .fillcolor ("#98FF66");


            sprintf (tmp, "%d\n", value.value_);
        }

        else if (value.type_ == 1)
        {
            dtNodeStyle ().fontcolor ("darkgreen")
                          .color     ("darkgreen")
                          .fillcolor ("#98FF66");


            sprintf (tmp, "var_%d\n", value.value_);
        }

        else
        {
            dtNodeStyle ().fontcolor ("red")
                          .color     ("red")
                          .fillcolor ("#FFCCC9");

            switch (value.type_)
            {
                case Add:   { sprintf (tmp, "+\n"); break; }
                case Sub:   { sprintf (tmp, "-\n"); break; }
                case Mul:   { sprintf (tmp, "*\n"); break; }
                case Div:   { sprintf (tmp, "/\n"); break; }
                case Equal: { sprintf (tmp, "=\n"); break; }

                default: break;
            }
        }
    }

    else sprintf (tmp, "%d %d", value.type_, value.value_);

    return string (tmp);
}
