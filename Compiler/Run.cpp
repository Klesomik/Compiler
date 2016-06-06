#include "Headers//Cpu.hpp"

//{==============================================================================

inline void Hello_Byte (std::string& example)
{ printf ("Input name of Byte file: "); getline (std::cin, example, '\n'); }

//Ú==============================================================================

int main (int argc, const char* argv[])
{
    try
    {
        std::string name_byte ("Materials//Byte.txt");

        //Hello_Byte (name_byte);

        FILE* file_byte = fopen (name_byte.c_str (), "r");

        Cpu cpu;
            cpu.read (file_byte);
            cpu.play ();

        fclose (file_byte);

        system ("pause");
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
