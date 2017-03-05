#ifndef LogHTML_hpp

#define LogHTML_hpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include "FormatBuffer.hpp"

class LogHTML
{
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
        void setSize      (const int size);
        void setStyle     (const char* style);
        void set          (const char* cmd, const char* value);
        void set          (const char* cmd, const int value);

        void picture (const char* src, const char* alt, const int width, const int height, const int hspace, const int vspace);

        void output (const char* message, ...);

        const char* name ();

    private:
        FormatBuffer file_;

        const char* name_;

        LogHTML (const LogHTML& from);

        LogHTML& operator = (LogHTML& from);
};

LogHTML::LogHTML ():
    file_ (),
    name_ ()
{
}

LogHTML::LogHTML (const char* title):
    file_ (),
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
    name_ = title;

    begin ("pre");
}

void LogHTML::close ()
{
    end ("pre");

    file_.to_file (name_);
}

void LogHTML::begin (const char* tag)
{
    file_.print ("<%s>\n", tag);
    file_.increase ();
}

void LogHTML::end (const char* tag)
{
    file_.print ("</%s>\n", tag);
    file_.decrease ();
}

void LogHTML::setColor (const char* color)
{
    set ("font color", color);
}

void LogHTML::setFontColor (const char* color)
{
    set ("body bgcolor", color);
}

void LogHTML::setSize (const int size)
{
    set ("font size", size);
}

void LogHTML::setStyle (const char* style)
{
    set ("font face", style);
}

void LogHTML::set (const char* cmd, const char* value)
{
    file_.print ("<%s = %s>\n", cmd, value);
}

void LogHTML::set (const char* cmd, const int value)
{
    file_.print ("<%s = %d>\n", cmd, value);
}

void LogHTML::picture (const char* src, const char* alt, const int width, const int height, const int hspace, const int vspace)
{
    file_.print ("<img src = %s alt = %s width = %d height = %d hspace = %d vspace = %d />\n", src, alt, width, height, hspace, vspace);
}

void LogHTML::output (const char* message, ...)
{
    const int size = 1000;

    char data[size] = "";

    va_list args;

    va_start (args, message);

    vsprintf (data, message, args);

    va_end (args);

    file_.print ("%s", data);
}

const char* LogHTML::name ()
{
    return name_;
}

void LogError (LogHTML& log, const std::string& message);

void LogError (LogHTML& log, const std::string& message)
{
    log.output ("%s\n", message);

    throw message.c_str ();
}

#endif /* LogHTML_hpp */
