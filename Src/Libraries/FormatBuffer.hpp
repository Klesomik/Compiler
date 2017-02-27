#ifndef FormatBuffer_hpp

#define FormatBuffer_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>

class FormatBuffer
{
    public:
        FormatBuffer ();
        FormatBuffer (int set_indent, int set_space);

        ~FormatBuffer ();

        void increase ();
        void decrease ();

        void print (const char* cmd, ...);

		void to_file (const std::string& name);

        char* buffer ();
        int& indent ();
        int& space ();

    private:
        char* buffer_;

        int indent_;
        int space_;
};

FormatBuffer::FormatBuffer ():
    buffer_ (new char[1000]),
    indent_ (0),
    space_  (4)
{
}

FormatBuffer::FormatBuffer (int set_indent, int set_space):
    buffer_ (new char[1000]),
    indent_ (set_indent),
    space_  (set_space)
{
}

FormatBuffer::~FormatBuffer ()
{
	delete[] buffer_;
}

void FormatBuffer::increase ()
{
    indent_ += space_;
}

void FormatBuffer::decrease ()
{
    indent_ -= space_;
}

void FormatBuffer::print (const char* cmd, ...)
{
    std::string tmp (indent_, ' ');

    sprintf (buffer_, "%s", tmp.c_str ());

    va_list args;

    va_start (args, cmd);

    vsprintf (buffer_, cmd, args);

    va_end (args);
}

void FormatBuffer::to_file (const std::string& name)
{
	FILE* file = fopen (name.c_str (), "w");

	assert (file);

	fprintf (file, "%s", buffer_);

	fclose (file);
			file = nullptr;
}

char* FormatBuffer::buffer ()
{
    return buffer_;
}

int& FormatBuffer::indent ()
{
    return indent_;
}

int& FormatBuffer::space ()
{
    return space_;
}

#endif /* FormatBuffer_hpp */
