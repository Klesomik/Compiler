#include "TXLib.h"

int main ()
{
    int i = 0;
    const int size = 1000000;
    while (true)
    {
        printf ("allocated %d memory\r", i);

        char* arr = new char [size]; //I am bad
        for (int j = 0; j < size; j ++) arr [j] =  (i + j) % 256;
        i += size;
    }

    return 0;
}
