#include "FileStream.hpp"

int main ()
{
    FileStream example ("Data.txt", "r");

    Stream <char> tmp;

    example.convert (tmp);

    return 0;
}
