#include "FileStream.hpp"

int main ()
{
    FileStream example ("Data.txt", "r");

    std::cout << example.size ();

    return 0;
}
