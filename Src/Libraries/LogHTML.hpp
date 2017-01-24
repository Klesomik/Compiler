#ifndef LogHTML_hpp
    #define LogHTML_hpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdarg>

class LogHTML
{
    private:
        FILE* file_;

        const char* name_;

        LogHTML (const LogHTML& from);

        LogHTML& operator = (LogHTML& from);

    public:
        LogHTML ();
        LogHTML (const char* title);

        ~LogHTML ();

        void open  (const char* title);
        void close ();

        void begin (const char* tag);
        void end   (const char* tag);

        void setColor     (const char* color);
        void setFontColor (const char* color);
        void setSize      (const size_t size);
        void setStyle     (const char* style);
        void set          (const char* cmd, const char* value);

        void picture (const char* src, const char* alt, const int width, const int height, const int hspace, const int vspace);

        void output (const char* message, ...);

        const char* name ();
};

LogHTML::LogHTML ():
    file_ (),
    name_ ()
{
}

LogHTML::LogHTML (const char* title):
    file_ (fopen (title, "w")),
    name_ (title)
{
    begin ("pre");
}

LogHTML::~LogHTML ()
{
    close ();
}

void LogHTML::open  (const char* title)
{
    if (!file_)
    {
        file_ = fopen (title, "w");
        name_ = title;

        assert (file_);

        fprintf (file_, "<pre>\n");
    }
}

void LogHTML::close ()
{
    if (file_)
    {
        end ("pre");

        fclose (file_);
                file_ = nullptr;
    }
}

void LogHTML::begin (const char* tag)
{
    fprintf (file_, "<%s>\n", tag);
}

void LogHTML::end (const char* tag)
{
    fprintf (file_, "</%s>\n", tag);
}

void LogHTML::setColor (const char* color)
{
    fprintf (file_, "<font color = %s>\n", color);
}

void LogHTML::setFontColor (const char* color)
{
    fprintf (file_, "<body bgcolor = %s>\n", color);
}

void LogHTML::setSize (const size_t size)
{
    fprintf (file_, "<font size = %u>\n", size);
}

void LogHTML::setStyle (const char* style)
{
    fprintf (file_, "<font face = %s>\n", style);
}

void LogHTML::set (const char* cmd, const char* value)
{
    fprintf (file_, "<%s = %s>\n", cmd, value);
}

void LogHTML::picture (const char* src, const char* alt, const int width, const int height, const int hspace, const int vspace)
{
    fprintf (file_, "<img src = %s alt = %s width = %d height = %d hspace = %d vspace = %d />\n", src, alt, width, height, hspace, vspace);
}

void LogHTML::output (const char* message, ...)
{
    va_list args;

    va_start (args, message);

    vfprintf (file_, message, args);

    va_end (args);
}

const char* LogHTML::name ()
{
    return name_;
}

#endif
