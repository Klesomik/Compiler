#include <cstdio>
#include <iostream>
#include "Headers//Cpu.hpp"

inline void Hello_Byte (std::string& example)
{ printf ("Input name of Byte file: "); getline (std::cin, example, '\n'); }

int main (int argc, const char* argv[])
{
    try
    {
        std::string name_byte ("..//Materials//Byte.txt");

        Hello_Byte (name_byte);

        FILE* file_byte = fopen (name_byte.c_str (), "r");

        assert (file_byte);

        std::vector <int> code;

        for (int cmd = 0; fscanf (file_byte, "%d", &cmd) != EOF;) code.push_back (cmd);

        fclose (file_byte);

        //Cpu cpu;
            //cpu.parsing (code);

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
