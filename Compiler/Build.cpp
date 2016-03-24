//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Librarys//Stream.hpp"
#include "Librarys//AbstractSyntaxNode.hpp"
#include "Headers//FrontEnd//LexicialAnalyzer.hpp"
#include "Headers//Compiler.hpp"
#include "Headers//FrontEnd//Optimizer.hpp"
#include "Headers//Assembler.hpp"

//}==============================================================================

//{==============================================================================

inline void Hello_C    (std::string& example)
{ printf ("Input name of C    file: "); getline (std::cin, example, '\n'); }

inline void Hello_Log  (std::string& example)
{ printf ("Input name of Log  file: "); getline (std::cin, example, '\n'); }

inline void Hello_Asm  (std::string& example)
{ printf ("Input name of Asm  file: "); getline (std::cin, example, '\n'); }

inline void Hello_Byte (std::string& example)
{ printf ("Input name of Byte file: "); getline (std::cin, example, '\n'); }

//}==============================================================================

//{==============================================================================

void C_to_Token         (Stream <Token>& code);
void Token_to_AST       (Stream <Token>& code, AstNode& root);
void AST_optimizer      (AstNode& root);
void AST_to_Asm_to_Byte (AstNode& root);

//}==============================================================================

int main (int argc, const char* argv[])
{
    try
    {
        Stream <Token> code;

        AstNode root ({ Block, Block });

        C_to_Token   (code);
        Token_to_AST (code, root);

        RenderTree (root, "EX3.dot");
    }
    catch (std::exception& message)
    {
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }
    catch (const int message)
    {
        std::cout << message << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error\n" << std::endl;
    }

    return 0;
}

//===============================================================================

void C_to_Token (Stream <Token>& code)
{
    std::string name;
    Hello_C (name);

    FILE* c_file = fopen (name.c_str (), "r");
    assert (c_file);

    LexicialAnalyzer lexicial_analyzer (c_file, code);

    fclose (c_file);
            c_file = nullptr;
}

//===============================================================================

void Token_to_AST (Stream <Token>& code, AstNode& root)
{
    std::string name;
    Hello_Log (name);

    LogHTML log (name.c_str ());

    log.setFontColor ("black");
    log.setSize      (100);
    log.setColor     ("yellow");

    log.output ("===== Build started  =====\n");

    Compiler compiler (root, code, log);

    log.output ("===== Build finished =====\n");

    log.close ();
}

//===============================================================================

void AST_optimizer (AstNode& root)
{
    Optimizer optimizer (root);
}

//===============================================================================

void AST_to_Asm_to_Byte (AstNode& root)
{
    std::string Asm_name;
    Hello_Asm (Asm_name);

    FILE* asm_code = fopen (Asm_name.c_str (), "w");
    assert (asm_code);

    std::string Byte_name;
    Hello_Byte (Byte_name);

    FILE* byte_code = fopen (Byte_name.c_str (), "w");
    assert (byte_code);

    fprintf (asm_code, "jmp main;\n");
    fprintf (asm_code, "label main;\n");

    Assembler assembler (root, asm_code, byte_code);

    fprintf (asm_code, "eof;\n");

    fclose (asm_code);
            asm_code = nullptr;

    fclose (byte_code);
            byte_code = nullptr;
}
