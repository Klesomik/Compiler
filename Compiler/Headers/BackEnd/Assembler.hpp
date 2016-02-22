//Namespace
//{==============================================================================

using namespace CpuCompiler;

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

map <string, int> Commands = {
                                #include "CommandsList.hpp"
                             };

#undef CMD

map <string, int> Regists = { { "ax", AX_ },
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

void Cmd_Push  (string& cmd, StrStream& command, Vector <int>& code_);
void Cmd_Pop   (string& cmd, StrStream& command, Vector <int>& code_);
void Cmd_In    (string& cmd, StrStream& command, Vector <int>& code_);
void Cmd_Out   (string& cmd, StrStream& command, Vector <int>& code_);
int  Cmd_Jmp   (Vector <Label>& label_, const string lb_name);
void Cmd_Label (Vector <int>& code_, Vector <Label>& label_, const string lb_name);
void Cmd_Else  (string& cmd, StrStream& command, Vector <int>& code_);

//}==============================================================================

//Class: Compiler
//{==============================================================================

class Compiler
{
    private:
        FILE* fixCode_;
        FILE* asmCode_;

        Vector <int>    code_;
        Vector <Label> label_;

        StrStream buff_;

        bool ok   ();
        void dump ();

    public:
        Compiler  ();
        Compiler  (const Compiler &from);
        ~Compiler ();

        Compiler& operator = (const Compiler &from);

        void read  ();
        void write ();

        FILE* FixCode () const;
        FILE* AsmCode () const;
};

//}==============================================================================

Compiler :: Compiler ():
    fixCode_ (fopen (InIt.Fix.c_str (), "r")),
    asmCode_ (fopen (InIt.Asm.c_str (), "w")),
    code_  (),
    label_ (),
    buff_  ()
    {
        assert (fixCode_ && asmCode_);

        copy (fixCode_, buff_);
    }

//===============================================================================

Compiler :: ~Compiler ()
{
    fclose (fixCode_);
    fclose (asmCode_);
}

//===============================================================================

void Compiler :: read ()
{
    while (true)
    {
        string cmd_arg;
        GetLine (buff_, cmd_arg, ';');
        if (cmd_arg == "") break;

        StrStream command (cmd_arg);

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

            #include "CommandsList.hpp"
        }

        #undef CMD
    }
}

//===============================================================================

void Compiler :: write ()
{
    for (size_t i = 0; i < code_.size (); i++)
    {
        fprintf (asmCode_, "%d ", code_[i]);

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

            fprintf (asmCode_, "%d ", code_[i]);
        }
    }
}

//===============================================================================

FILE* Compiler :: FixCode () const
{
    return fixCode_;
}

//===============================================================================

FILE* Compiler :: AsmCode () const
{
    return asmCode_;
}

//===============================================================================

void Cmd_Push (string& cmd, StrStream& command, Vector <int>& code_)
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

void Cmd_Pop (string& cmd, StrStream& command, Vector <int>& code_)
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

void Cmd_In (string& cmd, StrStream& command, Vector <int>& code_)
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

void Cmd_Out (string& cmd, StrStream& command, Vector <int>& code_)
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

void Cmd_Else (string& cmd, StrStream& command, Vector <int>& code_)
{
    cmd = StrTok (command, " ;\n");

    if (cmd != "") code_.push_back (atoi (cmd.c_str ()));
}
