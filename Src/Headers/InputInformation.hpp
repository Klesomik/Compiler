#ifndef Input_hpp

#define Input_hpp

#include <iostream>
#include <cstring>
#include <map>
#include "..//Libraries//Stream.hpp"
#include "..//Libraries//Tools.hpp"
#include "File.hpp"

struct File
{
    bool used;

    std::string name;

    File ();
    File (const bool set_used, const std::string& set_name);
};

File::File ():
    used (false),
    name ()
{
}

File::File (const bool set_used, const std::string& set_name):
    used (set_used),
    name (set_name)
{
}

class InputInformation
{
    public:
        InputInformation ();

        void parse (Stream <char>& info);

	private:
        File source,
             preproc,
             lexicial, dis_lexicial,
             syntax, dis_syntax,
             semantic, dis_semantic,
             optimizer,
             generator, dis_generator,
             translator, dis_translator;

        std::map <std::string, std::string*> files;
        //std::map <std::string, bool*> options;

		void space   (Stream <char>& example);
        void option  (Stream <char>& example);
        std::pair <bool, std::string> file (Stream <char>& example);
        void comment (Stream <char>& example);
};

InputInformation::InputInformation ():
    name_source   (),
    name_ast      (),
    name_dis_ast  (),
    name_asm      (),
    name_dis_asm  (),
    name_byte     (),
    name_dis_byte (),
    name_jit      (),
    name_dis_jit  (),
    name_log      (),
    preprocessor  (false),
    lexicial      (false),
    syntax        (false),
    semantic      (false),
    optimiser     (false),
    dissyntax     (false),
    generator     (false),
    disgenerator  (false),
    translator    (false),
    distranslator (false),
    jit           (false),
    disjit        (false),
    files         ({ {  "source", &name_source   },
                     {     "ast", &name_ast      },
                     {  "disast", &name_dis_ast  },
                     {     "asm", &name_asm      },
                     {  "disasm", &name_dis_asm  },
                     {    "byte", &name_byte     },
                     { "disbyte", &name_dis_byte },
                     {     "jit", &name_jit      },
                     {  "disjit", &name_dis_jit  },
                     {     "log", &name_log      } })
{
}

void InputInformation::space (Stream <char>& example)
{
    while (example.check () && IsSpace (example.current ()))
        example++;
}

void InputInformation::option (Stream <char>& example)
{
    example++; // -

    space (example);

    std::string name;

    while (example.check () && isalpha (example.current ()))
    {
        char symbol = 0;
        example >> symbol;

        name.push_back (symbol);
    }

    space (example);

    example++; // =

    space (example);

    std::string value;

    while (example.check () && isalpha (example.current ()))
    {
        char symbol = 0;
        example >> symbol;

        value.push_back (symbol);
    }

    space (example);

    example++; // ;

    if (value == "true")
        *(options[name]) = true;

    else
        *(options[name]) = false;
}

std::pair <bool, std::string> InputInformation::file (Stream <char>& example)
{
    example++; // @

    space (example);

    std::string name;

    while (example.check () && isalpha (example.current ()))
    {
        char symbol = 0;
        example >> symbol;

        name.push_back (symbol);
    }

    space (example);

    example++; // =

    space (example);

    example++; // "

    space (example);

    std::string path;

    while (example.check () && example.current () != '"')
    {
        char symbol = 0;
        example >> symbol;

        path.push_back (symbol);
    }

    space (example);

    example++; // "

    space (example);

    example++; // ;

    if (name == "config")
        return { true, path };

    *(files[name]) = path;

    return { false, "" };
}

void InputInformation::comment (Stream <char>& example)
{
    while (example.check () && example.current () != '\n')
        example++;
}

void InputInformation::parse (Stream <char>& info)
{
    while (info.check ())
    {
        if (IsSpace (info.current ()))
            space (info);

        else if (IsOption (info.current ()))
            option (info);

        else if (IsFile (info.current ()))
        {
            std::pair <bool, std::string> result (file (info));

            if (result.first)
            {
                FILE* input = fopen (result.second.c_str (), "r");

                Stream <char> example;

                CopyFile (example, input);

                fclose (input);

                parse (example);
            }
        }

        else if (IsConfigComment (info.current ()))
            comment (info);

        else
        {
            std::cout << info.current () << "\n\n";

            throw "Unknown symbol";
        }
    }
}

#endif
