#include "Parser.hpp"
#include "BackEnd.hpp"

using namespace std;

void Scan (Vector <char>& tmp);

int main (int argc, char* argv[])
{
    try
    {
        printf ("Deer: ");

        Vector <char> tmp;
        Scan (tmp);

        Stream <char> example (tmp);

        Stream <Token> code;
        Parser (example, code);

        BinaryNode <Token> root;
        NewGetE (root, code);

        FILE* asm_txt = fopen ("Data.txt", "w");

        CreateAsm (root, asm_txt);

        fclose (asm_txt);

        //printf ("Result = %d\n", CreateAsm (root, asm_txt));

        //DotDump (root, "EX1.dot");
    }
    catch (const char* message)
    {
        printf ("ERROR: %s\n", message);
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}

void Scan (Vector <char>& tmp)
{
    while (true)
    {
        char symbol = (char) getchar ();

        if (symbol == '\n') break;

        tmp.push_back (symbol);
    }
}

//Function for scan files
//{==============================================================================

inline void Hello_Boa () { printf ("Input name of Boa file: "); cin >> InIt.Boa; }
inline void Hello_Fix () { printf ("Input name of Fix file: "); cin >> InIt.Fix; }
inline void Hello_Asm () { printf ("Input name of Asm file: "); cin >> InIt.Asm; }

//}==============================================================================

