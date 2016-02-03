#ifndef WRAPPER_HPP_INCLUDED
    #define WRAPPER_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>

//}==============================================================================

//Define
//{==============================================================================

#define THROW(__FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__) Wrapper (__FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

//}==============================================================================

//Struct: Wrapper
//{==============================================================================

struct Wrapper
{
    char message_[1000];

    Wrapper (const char* file, const char* function, const size_t line);
};

//}==============================================================================

Wrapper :: Wrapper (const char* file, const char* function, const size_t line)
{
    throw message_;
}

#endif /* WRAPPER_HPP_INCLUDED */
