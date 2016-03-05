#ifndef DeerLib_hpp
    #define DeerLib_hpp

#include "..//..//Librarys//LogHTML.hpp"

class Source
{
    private:
        Source (const Source& from);

        Source& operator = (Source& from);

    public:
        FILE*   c_file;
        FILE* asm_file;

        LogHTML log_file;

        Source  ();
        ~Source ();

        void Hello_C   (std::string& example);
        void Hello_Asm (std::string& example);
        void Hello_Log (std::string& example);
};

Source :: Source ():
    c_file   (nullptr),
    asm_file (nullptr),
    log_file ()
    {
        std::string   c_name;
        std::string asm_name;
        std::string log_name;

        Hello_C     (c_name);
        Hello_Asm (asm_name);
        Hello_Log (log_name);

        c_file = fopen (c_name.c_str (), "r");
        assert (c_file);

        asm_file = fopen (asm_name.c_str (), "w");
        assert (asm_file);

        log_file.open (log_name.c_str ());
    }

Source :: ~Source ()
{
    fclose (c_file);
            c_file = nullptr;

    fclose (asm_file);
            asm_file = nullptr;

    log_file.close ();
}

void Source :: Hello_C (std::string& example)
{
    printf ("Input name of C   file: ");

    getline (cin, example, '\n');
}

void Source :: Hello_Asm (std::string& example)
{
    printf ("Input name of Asm file: ");

    getline (cin, example, '\n');
}

void Source :: Hello_Log (std::string& example)
{
    printf ("Input name of Log file: ");

    getline (cin, example, '\n');
}

Source Inform;

#endif
