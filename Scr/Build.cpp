//Include
//{==============================================================================

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Headers//InputInformation.hpp"
#include "Headers//Compiler.hpp"
#include "Headers//Assembler.hpp"

//}==============================================================================

void CmdLineInfo (InputInformation& scan);

int main (int argc, const char* argv[])
{
    try
    {
        InputInformation scan;
        CmdLineInfo (scan);

        Compiler compiler (scan);

        //Assembler assembler (name_asm, name_byte);
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
