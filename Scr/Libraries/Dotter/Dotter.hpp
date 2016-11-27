#ifndef Dotter_hpp

#define Dotter_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <dir.h>
#include <cstdlib>

namespace Dotter
{
    const char* Path = "\\Dot\\DotExe\\dot.exe";

    size_t Indent = 4;

    void SetPath    (const char* directory);
    void SetIndent  (const size_t space);

    const char* GetVersion ();

    namespace Details
    {
        void PrintIndent (FILE* file, const size_t ind);
        void AddIndent   (size_t& ind);
        void SubIndent   (size_t& ind);
        void Directory   (char* dir, size_t& dirSize);
        void Expansion   (const std::string& name, std::string& type);
        void StrInsert   (char* to, const char* from, size_t& counter);
    }
}

void Dotter::SetPath (const char* directory)
{
    Dotter::Path = directory;
}

void Dotter::SetIndent (const size_t space)
{
    Dotter::Indent = space;
}

const char* Dotter::GetVersion ()
{
    return "0.1";
}

void Dotter::Details::PrintIndent (FILE* file, const size_t ind)
{
    for (size_t i = 0; i < ind; i++)
        fprintf (file, " ");
}

void Dotter::Details::AddIndent (size_t& ind)
{
    ind += Dotter::Indent;
}

void Dotter::Details::SubIndent (size_t& ind)
{
    ind -= Dotter::Indent;
}

void Dotter::Details::Directory (char* dir, size_t& dirSize)
{
    while (!getcwd (dir, dirSize))
    {
        dirSize *= 2;

        delete[] dir;
                 dir = new char[dirSize];
    }
}

void Dotter::Details::Expansion (const std::string& name, std::string& type)
{
    size_t place = name.rfind ('.');

    for (size_t i = place + 1; i < name.size (); i++)
        type.push_back (name[i]);
}

void Dotter::Details::StrInsert (char* to, const char* from, size_t& counter)
{
    memcpy (to + counter, from, strlen (from));

    counter += strlen (from);
}

#include "Digraph.hpp"

#endif /* Dotter_hpp */
