#ifndef SPEAKER_HPP_INCLUDED
    #define SPEAKER_HPP_INCLUDED

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
    string message_; //char* !

    Wrapper (const string& file, const string& function, const size_t line);
};

//}==============================================================================

Wrapper :: Wrapper (const string& file, const string& function, const size_t line)
{
    throw message_;
}

#endif /* SPEAKER_HPP_INCLUDED */
