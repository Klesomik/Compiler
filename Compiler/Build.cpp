//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Headers//Compiler.hpp"
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

int main (int argc, const char* argv[])
{
    try
    {
        std::string name_c  ("Source.txt");
        std::string name_log  ("Log.html");
        std::string name_asm   ("Asm.txt");
        std::string name_byte ("Byte.txt");

        //Hello_C    (name_c);
        //Hello_Log  (name_log);
        //Hello_Asm  (name_asm);
        //Hello_Byte (name_byte);

        FILE* file_c = fopen (name_c.c_str (), "r");
        LogHTML file_log (name_log.c_str ());
        FILE* file_asm = fopen (name_asm.c_str (), "w");
        FILE* file_byte = fopen (name_byte.c_str (), "w");

        Compiler compiler (file_c, file_log, file_asm);

        fclose (file_asm);
        FILE* data = fopen (name_asm.c_str (), "r");

        //Assembler assembler (data, file_byte);

        fclose (file_c);
        fclose (data);
        fclose (file_byte);
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
