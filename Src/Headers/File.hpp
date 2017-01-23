#include <iostream>
#include "Stream.hpp"

struct File
{
    bool used;

    std::string name;

    File ();
    File (const bool set_used, const std::string& set_name);
};

File::File ():
    used (false),
    name ()
{
}

File::File (const bool set_used, const std::string& set_name):
    used (set_used),
    name (set_name)
{
}
