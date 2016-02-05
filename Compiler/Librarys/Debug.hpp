#ifndef DEBUG_HPP_INCLUDED
    #define DEBUG_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <iostream>

//}==============================================================================

//Define
//{==============================================================================

#define THROW(message)\
ErrorDump tmp (__FILE__, __PRETTY_FUNCTION__, __LINE__);\
Wrapper (tmp, message);

#define CATCH(message)\
printf ("\n==========THROW==========\n");\
\
std::cout << message << "\n";\
printf ("Message was caught at\nFILE: %s\nFUNC: %s\nLINE: %d\n", __FILE__, __FUNCTION__, __LINE__);\
\
printf ("=========================\n\n");

//__VA_ARGS__
//__DATE__
//__TIME__

//}==============================================================================

struct Log
{
};

struct ErrorDump
{
    char* file;
    char* function;
    int line;

    ErrorDump (const char* set_file, const char* set_function, const int set_line);
};

ErrorDump :: ErrorDump (const char* set_file, const char* set_function, const int set_line):
    file     (set_file),
    function (set_function),
    line     (set_line)
    {}

void Wrapper (ErrorDump& example, const char* label);

void Wrapper (ErrorDump& example, const char* label)
{
    char message[1000];

    sprintf ("Message was threw at\nFILE: %s\nFUNC: %s\nLINE: %d\n%s\n", example.file, example.function, example.line, label);

    throw message;
}

#endif /* DEBUG_HPP_INCLUDED */
