#include "TXLib.h"
#include "LogHTML.hpp"

int main ()
{
    LogHTML example ("Data.html");

    example.setColor ("red");
    example.setSize  (1200);

    example.output ("Ok");

    //example.close ();

    example.out ();

    return 0;
}
