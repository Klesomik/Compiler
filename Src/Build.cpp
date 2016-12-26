#include <cstdio>
#include <cstring>
#include <iostream>
#include "Headers//InputInformation.hpp"
#include "Headers//Compiler.hpp"
#include "Headers//Assembler.hpp"

void CmdLineInfo (InputInformation& scan);

int main (int argc, const char* argv[])
{
    try
    {
        InputInformation scan;
        CmdLineInfo (scan);

        //Compiler compiler (scan);

        //Assembler assembler (scan);
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

void CmdLineInfo (InputInformation& scan)
{
    Stream <char> cmd_line;

    GetLine (cmd_line, '\n');

    scan.parse (cmd_line);
}

/*void write (FILE* bit)
{
    #define BOA(id, params, name, word, comp, cpu) case id: { for (int j = 0; j < params; j++) { i++; fprintf (bit, "%d ", code_[i]); } break; }

    for (size_t i = 0; i < code_.size (); i++)
    {
        fprintf (bit, "%d ", code_[i]);

        switch (code_[i])
        {
            #include "BoaList.hpp"

            default: { break; }
        }
    }

    #undef BOA
}*/
