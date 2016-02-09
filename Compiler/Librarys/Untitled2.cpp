#include "TXLib.h"
#include "AbstractSyntaxTree.hpp"

int main ()
{
    try
    {
        BinaryNode <int> root (5);

        root.insert (7);
        root.insert (9);

        root.dump ();

        BinaryNode <int> example;

        example.dump ();
        root.dump ();
    }
    catch (const char* message)
    {
        printf ("ERROR: %s\n", message);
    }

    return 0;
}
