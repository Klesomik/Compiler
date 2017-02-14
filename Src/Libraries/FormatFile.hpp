#ifndef FormatFile_hpp

#define FormatFile_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>

class FormatFile
{
    public:
        FormatFile ();
        FormatFile (const std::string& set_file, int set_indent, int set_space);

        ~FormatFile ();

        void open (const std::string& name);
        void close ();

        void increase ();
        void decrease ();

        void print (const char* cmd, ...);

        FILE* file ();
        int& indent ();
        int& space ();

    private:
        FILE* file_;

        int indent_;
        int space_;
};

FormatFile::FormatFile ():
    file_   (nullptr),
    indent_ (0),
    space_  (4)
{
}

FormatFile::FormatFile (const std::string& set_file, int set_indent, int set_space):
    file_   (fopen (set_file.c_str (), "w")),
    indent_ (set_indent),
    space_  (set_space)
{
}

FormatFile::~FormatFile ()
{
    close ();
}

void FormatFile::open (const std::string& name)
{
    file_ = fopen (name.c_str (), "w");
}

void FormatFile::close ()
{
    if (file_)
    {
        fclose (file_);
                file_ = nullptr;
    }
}

void FormatFile::increase ()
{
    indent_ += space_;
}

void FormatFile::decrease ()
{
    indent_ -= space_;
}

void FormatFile::print (const char* cmd, ...)
{
    std::string tmp (indent_, ' ');

    fprintf (file_, "%s", tmp.c_str ());

    va_list args;

    va_start (args, cmd);

    vfprintf (file_, cmd, args);

    va_end (args);
}

FILE* FormatFile::file ()
{
    return file_;
}

int& FormatFile::indent ()
{
    return indent_;
}

int& FormatFile::space ()
{
    return space_;
}

#endif /* FormatFile_hpp */
