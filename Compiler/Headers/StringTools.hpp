//Include
//{==============================================================================

#include <cstring>
#include "..//Librarys//StrStream.hpp"

//}==============================================================================

//Namespace
//{==============================================================================

using std :: string;

//}==============================================================================

//Prototype
//{==============================================================================

string StrTok (StrStream& read, size_t* start, const char* separator);
string StrTok (StrStream& read, const char* separator);

void GetLine (FILE* code, string& token, const char delim);
void GetLine (StrStream& str_file, string& token, const char delim);

void Replace (string& cmd_arg, size_t start, size_t size, string& change);

void OkFile (const FILE* example);

void copy (FILE* code, string& buffer);
void copy (FILE* code, StrStream& buffer);

//}==============================================================================

string StrTok (StrStream& read, size_t* start, const char* separator)
{
    string token ("");

    bool first = true;

    for (size_t i = read.place (); i < read.size (); i++)
    {
        bool check = false;

        char symbol = 0;
        read >> symbol;

        for (size_t j = 0; j < strlen (separator); j++)
        {
            if (symbol == separator[j])
            {
                if (token == "") check = true;

                else return token;
            }
        }

        if (!check)
        {
            token += symbol;

            if (first)
            {
                (*start) = i;

                first = false;
            }
        }
    }

    return token;
}

//===============================================================================

string StrTok (StrStream& read, const char* separator)
{
    string token ("");

    for (size_t i = read.place (); i < read.size (); i++)
    {
        bool check = false;

        char symbol = 0;
        read >> symbol;

        for (size_t j = 0; j < strlen (separator); j++)
        {
            if (symbol == separator[j])
            {
                if (token == "") check = true;

                else return token;
            }
        }

        if (!check) token += symbol;
    }

    return token;
}

//===============================================================================

void GetLine (FILE* code, string& token, const char delim)
{
    for (char symbol = 0;;)
    {
        if (fscanf (code, "%c", &symbol) == EOF) break;
        if (symbol == delim) break;

        token += symbol;
    }
}

//===============================================================================

void GetLine (StrStream& str_file, string& token, const char delim)
{
    bool clear_buff = true;

    for (size_t i = str_file.place (); i < str_file.size (); i++)
    {
        char symbol = 0;
        str_file >> symbol;

        if (symbol == delim)
        {
            if (clear_buff) token = "";

            break;
        }

        else
        {
            token += symbol;

            if (symbol != ' ' &&
                symbol != '\n') clear_buff = false;
        }
    }

    if (clear_buff) token = "";
}

//===============================================================================

void Replace (string& cmd_arg, size_t start, size_t size, string& change)
{
    string buff;

    for (size_t i =     0; i <                  start; i++) buff.push_back (cmd_arg[i]);
    for (size_t i = start; i < change.size () + start; i++) buff.push_back (change[i - start]);
    for (size_t i = start + size; i < cmd_arg.size (); i++) buff.push_back (cmd_arg[i]);

    cmd_arg = buff;
}

//===============================================================================

void OkFile (const FILE* example)
{
    assert (example);
}

//===============================================================================

void copy (FILE* code, string& buffer)
{
    GetLine (code, buffer, '\0');
}

//===============================================================================

void copy (FILE* code, StrStream& buffer)
{
    string tmp;

    GetLine (code, tmp, '\0');

    buffer = tmp;
}
