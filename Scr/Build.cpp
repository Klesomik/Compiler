//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Headers//Compiler.hpp"
#include "Headers//Assembler.hpp"

//}==============================================================================

//{==============================================================================

inline void Input (const char* prefix, std::string& example)
{ printf ("%s", prefix); getline (std::cin, example, '\n'); }

//}==============================================================================

int main (int argc, const char* argv[])
{
    try
    {
        std::string name_c     ("..//Materials//main.txt");
        std::string name_log   ("..//Materials//Log.html");
        std::string name_asm   ("..//Materials//Asm.txt");
        std::string name_byte  ("..//Materials//Byte.txt");
        std::string name_tree  ("..//Materials//AST.txt");
        std::string name_graph ("..//Materials//AST.jpg");

        //Input ("Input name of C     file: ", name_c);
        //Input ("Input name of Log   file: ", name_log);
        //Input ("Input name of Asm   file: ", name_asm);
        //Input ("Input name of Byte  file: ", name_byte);
        //Input ("Input name of Tree  file: ", name_tree);
        //Input ("Input name of Graph file: ", name_graph);

        Compiler compiler (name_c, name_asm, name_log);

        Assembler assembler (name_asm, name_byte);
    }
    catch (std::exception& message)
    {
    }
    catch (const char* message)
    {
        std::cout << message << "\n";
    }
    catch (const int message)
    {
        std::cout << message << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown error\n" << "\n";
    }

    return 0;
}
