#include <stdio.h>
#include <cstring>
#include <map>
#include <iostream>
#include <cstdlib>

using namespace std;

class LogHTML
{
    private:
        FILE* file_;

    public:
        LogHTML (const char* title);

        ~LogHTML ();

        void open  (const char* title);
        void close ();

        void setColor (const char* color);
        void setSize  (const size_t size);
        void setStyle (const char* style);

        void output (const char* message);

        void out ();
};

LogHTML :: LogHTML (const char* title):
    file_ (fopen (title, "w"))
    { fprintf (file_, "<pre>\n"); }

LogHTML :: ~LogHTML ()
{
    close ();
}

void LogHTML :: open  (const char* title)
{
    if (!file_) file_ = fopen (title, "w");
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

void LogHTML :: setSize (const size_t size)
{
    fprintf (file_, "<font size = %d>\n", size);
}

void LogHTML :: setStyle (const char* style)
{
    fprintf (file_, "<font face = %s>\n", style);
}

void LogHTML :: output (const char* message)
{
    fprintf (file_, "%s\n", message);
}

void LogHTML :: out ()
{
    printf ("%s", file_ -> _base);
}
