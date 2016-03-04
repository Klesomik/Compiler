//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Librarys//Debug.hpp"
#include "Librarys//Stream.hpp"
#include "Librarys//AbstractSyntaxTree.hpp"
#include "Headers//FrontEnd//LexicialAnalyzer.hpp"
#include "Headers//FrontEnd//SyntaxAnalyzer.hpp"
#include "Headers//FrontEnd//TreeCheck.hpp"
#include "Headers//BackEnd//Compiler.hpp"

//}==============================================================================

using namespace std;

//{==============================================================================

inline void Hello_C   (std::string& example) { printf ("Input name of C   file: "); getline (cin, example, '\n'); }
inline void Hello_Asm (std::string& example) { printf ("Input name of Asm file: "); getline (cin, example, '\n'); }
inline void Hello_Log (std::string& example) { printf ("Input name of Log file: "); getline (cin, example, '\n'); }

//}==============================================================================

//{==============================================================================

void ParserGenerate (Stream <Token>& code);
void TreeGenerate (AstNode& root, Stream <Token>& code);
void AsmGenerate (AstNode& root);

//}==============================================================================

int main (int argc, const char* argv[])
{
    try
    {
        TRY

        Stream <Token> code;

        ParserGenerate (code);

        AstNode root ({ None, None });

        std::string example;
        Hello_Log (example);

        Log.rename (example.c_str ());

        TreeGenerate (root, code);

        Check check (root);
        //AsmGenerate (root);

        DotDump (root, "EX1.dot");
    }
    catch (std::exception)
    {
    }
    catch (const char* message)
    {
        CATCH
    }
    catch (const int message)
    {
    }
    catch (...)
    {
        printf ("Unknown error\n");
    }

    return 0;
}

//===============================================================================

void ParserGenerate (Stream <Token>& code)
{
    std::string C_name;
    Hello_C (C_name);

    FILE* C_File = fopen (C_name.c_str (), "r");
    assert (C_File);

    Stream <char> example;

    for (char symbol = 0; fscanf (C_File, "%c", &symbol) != EOF;)
    {
        example.push_back (symbol);
    }

    Parser (example, code);

    fclose (C_File);
}

//===============================================================================

void TreeGenerate (AstNode& root, Stream <Token>& code)
{
    while (code.check ())
    {
        AstNode current ({ None, None });

        Get_Block (current, code);

        root.insert (current);
    }
}

//===============================================================================

void AsmGenerate (AstNode& root)
{
    std::string Asm_name;
    Hello_Asm (Asm_name);

    FILE* asm_code = fopen (Asm_name.c_str (), "w");
    assert (asm_code);

    fprintf (asm_code, "jmp main;\n");
    fprintf (asm_code, "label main;\n");

    for (size_t i = 0; i < root.children ().size (); i++)
        CreateAsm (root.children ()[i], asm_code);

    fprintf (asm_code, "eof;\n");

    fclose (asm_code);
}
