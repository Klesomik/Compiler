#pragma once

//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <iostream>
#include "Vector.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define TRY\
range.Try (__FILE__, __PRETTY_FUNCTION__, __LINE__);\
try

#define THROW(message)\
{\
    range.Throw (__FILE__, __PRETTY_FUNCTION__, __LINE__);\
    range.Wrapper (message);\
}

#define CATCH{\
catch (const char* message)\
{\
    std::cout << message << "\n";\
\
    printf (indent, "Message was caught at\n");\
\
    printf (indent, "  FILE: %s\n", __FILE__);\
    printf (indent, "  FUNC: %s\n", __PRETTY_FUNCTION__);\
    printf (indent, "  LINE: %d\n", __LINE__);

//__VA_ARGS__
//__DATE__
//__TIME__

//}==============================================================================

struct ErrorDump
{
    const char*  file_try;
    const char*  function_try;
    size_t line_try;

    const char*  file_throw;
    const char*  function_throw;
    size_t line_throw;

    char message[2048];

    ErrorDump ();

    void Try   (const char*   set_file_try, const char*   set_function_try, const size_t   set_line_try);
    void Throw (const char*   set_file_try, const char*   set_function_try, const size_t   set_line_try);

    void Wrapper (const char* label);
};

ErrorDump :: ErrorDump ():
    file_try       (),
    function_try   (),
    line_try       (),
    file_throw     (),
    function_throw (),
    line_throw     (),
    message        ()
    {}

void ErrorDump :: Try (const char* set_file_try, const char* set_function_try, const size_t set_line_try)
{
    file_try     = set_file_try;
    function_try = set_function_try;
    line_try     = set_line_try;
}

void ErrorDump :: Throw (const char* set_file_throw, const char* set_function_throw, const size_t set_line_throw)
{
    file_throw     = set_file_throw;
    function_throw = set_function_throw;
    line_throw     = set_line_throw;
}

void ErrorDump :: Wrapper (const char* label)
{
    size_t indent = 0;

    indent += sprintf (message + indent, "Message was tried at\n");

    indent += sprintf (message + indent, "  FILE: %s\n", file_try);
    indent += sprintf (message + indent, "  FUNC: %s\n", function_try);
    indent += sprintf (message + indent, "  LINE: %d\n", line_try);

    indent += sprintf (message + indent, "Message was threw at\n");

    indent += sprintf (message + indent, "  FILE: %s\n", file_throw);
    indent += sprintf (message + indent, "  FUNC: %s\n", function_throw);
    indent += sprintf (message + indent, "  LINE: %d\n", line_throw);

    indent += sprintf (message + indent, "%s\n", label);

    sprintf (message + indent, "Message was wrapped in Wrapper\n");

    throw message;
}

ErrorDump range;
