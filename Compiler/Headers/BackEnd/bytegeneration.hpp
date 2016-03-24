//Include
//{==============================================================================

#include <map>
#include "..//..//Librarys//Stream.hpp"

//}==============================================================================

string StrTok (Stream <char>& read, const char* separator);

void GetLine (FILE* code, Stream <char>& token, const char delim);
void GetLine (Stream <char>& code, Stream <char>& token, const char delim);

string StrTok (Stream <char>& read, const char* separator)
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

void GetLine (FILE* code, Stream <char>& token, const char delim)
{
    for (char symbol = 0;;)
    {
        if (fscanf (code, "%c", &symbol) == EOF) break;
        if (symbol == delim) break;

        token.push_back (symbol);
    }
}

void GetLine (Stream <char>& code, Stream <char>& token, const char delim)
{
    while (code.check ())
    {
        char symbol = 0;
        code >> symbol;

        if (symbol == delim) break;

        token.push_back (symbol);
    }
}

//Enum
//{==============================================================================

#define CMD(id, name, pre, comp, cpu) CMD_##name,

enum CmdNum {
                CMD_first = 0,

                #include "..//CommandsList.hpp"

                CMD_last
            };

#undef CMD

//}==============================================================================

//Global constant
//{==============================================================================

static const char Separator[2] = " ";

//}==============================================================================

//Enum
//{==============================================================================

enum NameRegist { AX_, BX_, CX_, DX_,
                  AY_, BY_, CY_, DY_,
                  AZ_, BZ_, CZ_, DZ_ };

//}==============================================================================

//Map
//{==============================================================================

#define CMD(id, name, pre, comp, cpu) { #name, CMD_##name },

std::map <string, int> Commands = {
                                      #include "..//CommandsList.hpp"
                                  };

#undef CMD

std::map <string, int> Regists = { { "ax", AX_ },
                                   { "bx", BX_ },
                                   { "cx", CX_ },
                                   { "dx", DX_ },
                                   { "ay", AY_ },
                                   { "by", BY_ },
                                   { "cy", CY_ },
                                   { "dy", DY_ },
                                   { "az", AZ_ },
                                   { "bz", BZ_ },
                                   { "cz", CZ_ },
                                   { "dz", DZ_ } };

//}==============================================================================

//Struct: Label
//{==============================================================================

struct Label
{
    string name_;

    int line_;

    Label ();
    Label (const string nick, const int value);
};

Label :: Label ():
    name_ (""),
    line_ (-1)
    {}

Label :: Label (const string nick, const int value):
    name_ (nick),
    line_ (value)
    {}

//}==============================================================================

//Prototype
//{==============================================================================

void Cmd_Push  (string& cmd, Stream <char>& command, Vector <int>& code_);
void Cmd_Pop   (string& cmd, Stream <char>& command, Vector <int>& code_);
void Cmd_In    (string& cmd, Stream <char>& command, Vector <int>& code_);
void Cmd_Out   (string& cmd, Stream <char>& command, Vector <int>& code_);
int  Cmd_Jmp   (Vector <Label>& label_, const string lb_name);
void Cmd_Label (Vector <int>& code_, Vector <Label>& label_, const string lb_name);
void Cmd_Else  (string& cmd, Stream <char>& command, Vector <int>& code_);

//}==============================================================================

//Class: ByteGeneration
//{==============================================================================

class ByteGeneration
{
    private:
        Vector <int>    code_;
        Vector <Label> label_;

        Stream <char> buff_;

        ByteGeneration  (const ByteGeneration &from);

        ByteGeneration& operator = (const ByteGeneration &from);

    public:
        ByteGeneration  (FILE* boa, FILE* bit);

        void read  ();
        void write (FILE* bit);
};

//}==============================================================================

ByteGeneration :: ByteGeneration (FILE* boa, FILE* bit):
    code_  (),
    label_ (),
    buff_  ()
    {
        GetLine (boa, buff_, '\0');

        read  ();
        write (bit);
    }

//===============================================================================

void ByteGeneration :: read ()
{
    while (true)
    {
        Stream <char> command;

        GetLine (buff_, command, ';');
        if (command.empty ()) break;

        #define CMD(id, name, pre, comp, cpu)\
        if (cmd == #name)\
        {\
            comp\
        }

        while (true)
        {
            string cmd (StrTok (command, " ;\n")); //token
            if (cmd == "") break;

            if (cmd != "label") code_.push_back (Commands[cmd]);

            #include "..//CommandsList.hpp"
        }

        #undef CMD
    }
}

//===============================================================================

void ByteGeneration :: write (FILE* bit)
{
    for (size_t i = 0; i < code_.size (); i++)
    {
        fprintf (bit, "%d ", code_[i]);

        if (code_[i] == CMD_jmp  ||
            code_[i] == CMD_je   ||
            code_[i] == CMD_jne  ||
            code_[i] == CMD_jl   ||
            code_[i] == CMD_jle  ||
            code_[i] == CMD_jm   ||
            code_[i] == CMD_jme  ||
            code_[i] == CMD_call)
        {
            i++;

            code_[i] = label_[code_[i]].line_;

            fprintf (bit, "%d ", code_[i]);
        }
    }
}

//===============================================================================

void Cmd_Push (string& cmd, Stream <char>& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    int type = atoi (cmd.c_str ());

    if (type == 0)
    {
        if (cmd[0] == '%')
        {
            code_.push_back (1);
            code_.push_back (atoi (cmd.c_str () + 1));
        }

        else
        {
            code_.push_back (0);
            code_.push_back (Regists[cmd]);
        }
    }

    else
    {
        code_.push_back (2);
        code_.push_back (type);
    }
}

//===============================================================================

void Cmd_Pop (string& cmd, Stream <char>& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    if (cmd == "")
    {
        code_.push_back (0);
    }

    else
    {
        if (cmd[0] == '%')
        {
            code_.push_back (1);
            code_.push_back (atoi (cmd.c_str () + 1));
        }

        else
        {
            code_.push_back (2);
            code_.push_back (Regists[cmd]);
        }
    }
}

//===============================================================================

void Cmd_In (string& cmd, Stream <char>& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    if (cmd[0] == '%')
    {
        code_.push_back (0);
        code_.push_back (atoi (cmd.c_str () + 1));
    }

    else
    {
        code_.push_back (1);
        code_.push_back (Regists[cmd]);
    }
}

//===============================================================================

void Cmd_Out (string& cmd, Stream <char>& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    if (cmd[0] == '%')
    {
        code_.push_back (0);
        code_.push_back (atoi (cmd.c_str () + 1));
    }

    else
    {
        code_.push_back (1);
        code_.push_back (Regists[cmd]);
    }
}

//===============================================================================

int Cmd_Jmp (Vector <Label>& label_, const string lb_name)
{
    for (size_t i = 0; i < label_.size (); i++)
    {
        if (lb_name == label_[i].name_) return i;
    }

    label_.push_back ({ lb_name, -1 });

    return label_.size () - 1;
}

//===============================================================================

void Cmd_Label (Vector <int>& code_, Vector <Label>& label_, const string lb_name)
{
    for (size_t i = 0; i < label_.size (); i++)
    {
        if (lb_name == label_[i].name_)
        {
            label_[i].line_ = code_.size (); //

            return;
        }
    }

    Label code_ptr (lb_name, code_.size ());

    label_.push_back (code_ptr);
}

//===============================================================================

void Cmd_Else (string& cmd, Stream <char>& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    if (cmd != "") code_.push_back (atoi (cmd.c_str ()));
}
