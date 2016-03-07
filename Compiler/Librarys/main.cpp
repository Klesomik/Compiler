#include "AbstractSyntaxTree.hpp"

int main ()
{
    try
    {
        AstNode root ({ None });
        root.insert ({ Digit, 5 });
        root.insert ({ Var, "a" });
        root.insert ({ Mul });
        root[0] -> erase ();

        root.dump ();
        //root[0] -> insert ({ Assignment });
        //root[0] -> insert ();
        //root[0][0].erase ();

        //DotDump (root, "EX2.dot");
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}
