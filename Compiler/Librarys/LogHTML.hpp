#ifndef LogHTML_hpp
    #define LogHTML_hpp

//{==============================================================================

#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <cstdlib>
#include <cstdarg>

//}==============================================================================

//{==============================================================================

using namespace std;

//}==============================================================================

//{==============================================================================

class LogHTML
{
    private:
        FILE* file_;

        const char* name_;

        LogHTML (const LogHTML& from);

        LogHTML& operator = (LogHTML& from);

    public:
        LogHTML (const char* title);
        LogHTML ();

        ~LogHTML ();

        void open  (const char* title);
        void close ();

        void setColor     (const char* color);
        void setFontColor (const char* color);
        void setSize      (const size_t size);
        void setStyle     (const char* style);

        void output (const char* message, ...);

        void out ();

        const char* name ();
};

//}==============================================================================

LogHTML :: LogHTML (const char* title):
    file_ (fopen (title, "w")),
    name_ (title)
    {
        assert (file_);

        fprintf (file_, "<pre>\n");
    }

LogHTML :: LogHTML ():
    file_ (nullptr),
    name_ ()
    {}

LogHTML :: ~LogHTML ()
{
    close ();
}

void LogHTML :: open  (const char* title)
{
    if (!file_)
    {
        file_ = fopen (title, "w");
        name_ = title;

        assert (file_);

        fprintf (file_, "<pre>\n");
    }
}

void LogHTML :: close ()
{
    if (file_)
    {
        fclose (file_);
                file_ = nullptr;
    }
}

void LogHTML :: setColor (const char* color)
{
    fprintf (file_, "<font color = %s>\n", color);
}

void LogHTML :: setFontColor (const char* color)
{
    fprintf (file_, "<body bgcolor = %s>\n", color);
}

void LogHTML :: setSize (const size_t size)
{
    fprintf (file_, "<font size = %d>\n", size);
}

void LogHTML :: setStyle (const char* style)
{
    fprintf (file_, "<font face = %s>\n", style);
}

void LogHTML :: output (const char* message, ...)
{
    va_list args;
    va_start (args, message);

    for (const char* ptr = message; *ptr; ptr++)
    {
        if (*ptr == '%')
        {
            switch (*++ptr)
            {
                case 'd': { int value    = va_arg (args, int);    fprintf (file_, "%d", value); break; }

                case 'f': { double value = va_arg (args, double); fprintf (file_, "%f", value); break; }

                default:  { break; }
            }
        }

        else fprintf (file_, "%c", *ptr);
    }

    va_end (args);
}

void LogHTML :: out ()
{
}

const char* LogHTML :: name ()
{
    return name_;
}

#endif
