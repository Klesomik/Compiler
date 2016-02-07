#ifndef DEBUG_HPP_INCLUDED
    #define DEBUG_HPP_INCLUDED

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
ErrorDump tmp;\
tmp.Try (__FILE__, __PRETTY_FUNCTION__, __LINE__);\
TryList.push_back (tmp)

#define THROW(message)\
{\
    TryList.back ().Catch (__FILE__, __PRETTY_FUNCTION__, __LINE__);\
    TryList.back ().Wrapper (message);\
}

#define CATCH(message)\
{\
    printf ("\n==========ERROR==========\n");\
    \
    std::cout << message << "\n";\
    printf ("Message was caught at\n");\
    printf ("   FILE: %s\n", __FILE__);\
    printf ("   FUNC: %s\n", __FUNCTION__);\
    printf ("   LINE: %d\n", __LINE__);\
    \
    printf ("=========================\n\n");\
}

//__VA_ARGS__
//__DATE__
//__TIME__

//}==============================================================================

struct Log
{
};

struct ErrorDump
{
    const char*  file_try;
    const char*  function_try;
    size_t line_try;

    const char*  file_catch;
    const char*  function_catch;
    size_t line_catch;

    char message[2048];

    ErrorDump ();

    void Try   (const char*   set_file_try, const char*   set_function_try, const size_t   set_line_try);
    void Catch (const char* set_file_catch, const char* set_function_catch, const size_t set_line_catch);

    void Wrapper (const char* label);
};

ErrorDump :: ErrorDump ():
    file_try       (),
    function_try   (),
    line_try       (),
    file_catch     (),
    function_catch (),
    line_catch     (),
    message        ()
    {}

void ErrorDump :: Try (const char* set_file_try, const char* set_function_try, const size_t set_line_try)
{
    file_try     = set_file_try;
    function_try = set_function_try;
    line_try     = set_line_try;
}

void ErrorDump :: Catch (const char* set_file_catch, const char* set_function_catch, const size_t set_line_catch)
{
    file_catch     = set_file_catch;
    function_catch = set_function_catch;
    line_catch     = set_line_catch;
}

void ErrorDump :: Wrapper (const char* label)
{
    size_t indent = 0;

    indent += sprintf (message + indent, "Message was threw at\n");

    indent += sprintf (message + indent, "  FILE: %s\n", file_try);
    indent += sprintf (message + indent, "  FUNC: %s\n", function_try);
    indent += sprintf (message + indent, "  LINE: %d\n", line_try);

    indent += sprintf (message + indent, "%s\n", label);

    sprintf (message + indent, "Message was wrapped in Wrapper\n");

    throw message;
}

Vector <ErrorDump> TryList;

#endif /* DEBUG_HPP_INCLUDED */
