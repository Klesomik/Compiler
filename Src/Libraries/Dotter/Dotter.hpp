#ifndef Dotter_hpp

#define Dotter_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

namespace Dotter
{
    const char* GetVersion ();

    namespace Details
    {
        void Expansion (const std::string& name, std::string& type);
    }
}

const char* Dotter::GetVersion ()
{
    return "0.1";
}

void Dotter::Details::Expansion (const std::string& name, std::string& type)
{
    size_t place = name.rfind ('.');

    for (size_t i = place + 1; i < name.size (); i++)
        type.push_back (name[i]);
}

#include "Digraph.hpp"

#endif /* Dotter_hpp */
