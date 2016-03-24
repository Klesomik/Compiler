//Include
//{==============================================================================

#include <map>
#include "..//Librarys//StrStream.hpp"

//}==============================================================================

//Namespace
//{==============================================================================

using std :: map;
using std :: pair;

//}==============================================================================

//Prototype
//{==============================================================================

string StrTok (Stream <char>& read, size_t* start, const char* separator);

void GetLine (FILE* code, string& token, const char delim);
void GetLine (Stream <char>& str_file, string& token, const char delim);

void Replace (string& cmd_arg, size_t start, size_t size, string& change);

//}==============================================================================

string StrTok (Stream <char>& read, size_t* start, const char* separator)
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

void GetLine (FILE* code, string& token, const char delim)
{
    for (char symbol = 0;;)
    {
        if (fscanf (code, "%c", &symbol) == EOF) break;
        if (symbol == delim) break;

        token.push_back (symbol);
    }
}

//===============================================================================

void GetLine (Stream <char>& str_file, string& token, const char delim)
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

//Constants
//{==============================================================================

//const char CmdProProc[][] = {    "link",
                              //"replace" };

//}==============================================================================

//Map
//{==============================================================================

map <string, string> Defines = {};

//}==============================================================================

class PreProcessor;

void CmdCheck (string& cmd_arg, size_t  cmd_place, string& cmd);
void CmdLink  (string&     cmd, size_t& cmd_place, StrStream& command, string& cmd_arg, PreProcessor& example);
void CmdReplace (StrStream& command, size_t& cmd_place);

//Class: PreProcessor
//{==============================================================================

class PreProcessor
{
    private:
        FILE* boaCode_;
        FILE* fixCode_;

        string buff_;

    public:
        PreProcessor  ();
        PreProcessor  (const PreProcessor& from);
        ~PreProcessor ();

        PreProcessor& operator = (const PreProcessor& from);

        void read   (FILE* file);
        void write  ();

        FILE* BoaCode () const;
        FILE* FixCode () const;
};

//}==============================================================================

PreProcessor :: PreProcessor ():
    boaCode_ (fopen (InIt.Boa.c_str (), "r")),
    fixCode_ (fopen (InIt.Fix.c_str (), "w")),
    buff_    ()
    { assert (boaCode_ && fixCode_); }

//===============================================================================

PreProcessor :: ~PreProcessor ()
{
    fclose (boaCode_);
    fclose (fixCode_);
}

//===============================================================================

void PreProcessor :: read  (FILE* file)
{
    string code;
    copy (file, code);

    StrStream str_file (code);

    while (true)
    {
        string cmd_arg; // From here

        GetLine (str_file, cmd_arg, ';');

        if (cmd_arg == "") break;

        size_t cmd_place = 0;
        StrStream command (cmd_arg); // Out of cmd_arg

        #define CMD(id, name, pre, comp, cpu)\
        if (cmd == #name)\
        {\
            pre\
        }

        while (true)
        {
            string cmd (StrTok (command, &cmd_place, " ;\n"));

            CmdCheck (cmd_arg, cmd_place, cmd);

            #include "CommandsList.hpp"
        }

        #undef CMD

        if (cmd_arg != "") buff_ += cmd_arg + ';';
    }
}

//===============================================================================

void PreProcessor :: write ()
{
    for (size_t i = 0; i < buff_.size (); i++)
    {
        fprintf (fixCode_, "%c", buff_[i]);
    }
}

//===============================================================================

FILE* PreProcessor :: BoaCode () const
{
    return boaCode_;
}

//===============================================================================

FILE* PreProcessor :: FixCode () const
{
    return fixCode_;
}

//===============================================================================

void CmdCheck (string& cmd_arg, size_t cmd_place, string& cmd)
{
    for (auto it = Defines.begin (); it != Defines.end (); it++)
    {
        if (cmd == it -> first) Replace (cmd_arg, cmd_place, cmd.size (), it -> second);
    }
}

//===============================================================================

void CmdLink (string& cmd, size_t& cmd_place, StrStream& command, string& cmd_arg, PreProcessor& example)
{
    cmd = StrTok (command, &cmd_place, " \";");

    cmd_arg = "";

    FILE* tmp = fopen (cmd.c_str (), "r");

    OkFile (tmp);

    example.read (tmp);

    fclose (tmp);
}

//===============================================================================

void CmdReplace (StrStream& command, size_t& cmd_place)
{
    string var  (StrTok (command, &cmd_place, " ;\n"));
    string nick (StrTok (command, &cmd_place, " ;\n"));

    Defines.insert (pair <string, string> (var, nick));
}
