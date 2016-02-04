#ifndef DEBUG_HPP_INCLUDED
    #define DEBUG_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>

//}==============================================================================

//Define
//{==============================================================================

#define THROW Wrapper ();

//__PRETTY_FUNCTION__
//__VA_ARGS__
//__DATE__
//__TIME__

//}==============================================================================

void Wrapper ()
{
    char message[1000];

    sprintf (message, "\n==========THROW==========\nFILE: %s\nFUNC: %s\nLINE: %d\n=========================\n\n",
    __FILE__, __FUNCTION__, __LINE__);

    throw message;
}

#endif /* DEBUG_HPP_INCLUDED */
