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
    fprintf (file_, "<font size = %zu>\n", size);
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
                case 'd': { int    value = va_arg (args,    int); fprintf (file_, "%d", value); break; }
                case 'f': { double value = va_arg (args, double); fprintf (file_, "%f", value); break; }
                case 's': { char*  value = va_arg (args,  char*); fprintf (file_, "%s", value); break; }

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

void LogBegin (LogHTML& log);
void LogEnd (LogHTML& log, clock_t begin, clock_t end);
void LogError (LogHTML& log, const char* message);

void LogBegin (LogHTML& log)
{
    log.setFontColor ("white");
    log.setSize      (50);
    log.setColor     ("blue");

    log.setColor ("gray");
    log.output ("DeerC %d.%d\n\n", 1, 0);

    log.setColor ("blue");
    log.output ("========== Build started ==========\n");

    log.setColor ("red");
}

void LogEnd (LogHTML& log, clock_t begin, clock_t end)
{
    log.setColor ("blue");
    log.output ("========== Build finished ==========\n\n");

    log.setColor ("gray");
    log.output ("Build started on: %f\n",   (float) begin / CLOCKS_PER_SEC);
    log.output ("Build   ended on: %f\n\n", (float)   end / CLOCKS_PER_SEC);

    log.out ();
}

void LogError (LogHTML& log, const char* message)
{
    log.output (message);

    throw message;
}

/*template <typename <Data_T>>
std::ostream& operator << (LogHTML& log, const Data_T& value);

template <typename <Data_T>>
LogHTML& operator << (LogHTML& log, const Data_T& value)
{
    log.output ("%d", value);

    return log;
}*/

#endif
