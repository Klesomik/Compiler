#include "BinaryNode.hpp"
#include <cstring>

using namespace std;

int main ()
{
    try
    {
        Token tmp_1 (0, 1);
        Token tmp_2 (0, 2);
        Token tmp_3 (0, 3);

        BinaryNode <Token> root (tmp_1);

        root.insertLeft  (tmp_2);
        root.insertRight (tmp_3);

        DotDump (root, "EX1");
    }
    catch (const char* message)
    {
        printf ("ERROR: %s\n", message);
    }

    return 0;
}
