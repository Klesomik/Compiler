#include <iostream>
#include <cstring>
#include <map>
#include "..//Libraries//Stream.hpp"

class InputInformation
{
    public:
        InputInformation ();

        void parse (Stream <char>& info);

        bool is_space   (const char symbol);
        bool is_option  (const char symbol);
        bool is_file    (const char symbol);
        bool is_comment (const char symbol);

        void space   (Stream <char>& example);
        void option  (Stream <char>& example);
        std::pair <bool, std::string> file (Stream <char>& example);
        void comment (Stream <char>& example);

        std::string name_source,
                    name_ast,
                    name_dis_ast,
                    name_asm,
                    name_dis_asm,
                    name_byte,
                    name_dis_byte,
                    name_jit,
                    name_dis_jit,
                    name_log;

        bool lexicial,
             syntax,
             semantic,
             optimiser,
             disast,
             generator,
             disasm,
             translator,
             disbyte,
             jit,
             disjit;

        std::map <std::string, std::string*> files;
        std::map <std::string, bool*> options;
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

bool InputInformation::is_space (const char symbol)
{
    return symbol == ' ' || symbol == '\n';
}

bool InputInformation::is_option (const char symbol)
{
    return symbol == '-';
}

bool InputInformation::is_file (const char symbol)
{
    return symbol == '@';
}

bool InputInformation::is_comment (const char symbol)
{
    return symbol == '#';
}

void InputInformation::space (Stream <char>& example)
{
    while (example.check () && is_space (example.current ()))
        example++;
}

void InputInformation::option (Stream <char>& example)
{
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
        if (is_space (info.current ()))
            space (info);

        else if (is_option (info.current ()))
            option (info);

        else if (is_file (info.current ()))
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

        else if (is_comment (info.current ()))
            comment (info);

        else
        {
            std::cout << info.current () << "\n\n";

            throw "Unknown symbol";
        }
    }
}
