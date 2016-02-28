#include "AbstractSyntaxTree.hpp"

int main ()
{
    AstNode root ({ Add, 0 });
    AstNode sub_root ({ Mul, 0 });

    AstNode* copy_root = nullptr;
    copy_root = &sub_root;
    sub_root.dump ();
    copy_root -> dump ();

    return 0;
}
