#include <cstdio>
#include <cstring>
#include <iostream>
#include "Headers//Compiler.hpp"
#include "Headers//Assembler.hpp"

int main (int argc, const char* argv[])
{
    try
    {
        std::string file;
        std::getline (std::cin, file, '\n');

        Compiler compiler;

        Tools::Read (compiler.first, file);

        Stream <char> to;

        compiler.run (to);

        Assembler assembler;
                  assembler.run (to);
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
