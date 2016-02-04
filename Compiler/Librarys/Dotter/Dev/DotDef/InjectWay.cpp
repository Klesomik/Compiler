#include "stdio.h"

int main (int n, char** arg)
{
    if (n != 2) return -1;
    
    FILE* To = fopen ("..\\Dot\\DotDef.h", "w");
    
    fprintf (To, "#ifdef __DOT__\n"); 
    fprintf (To, "    #warning __DOT__ can be not correct\n");
    fprintf (To, "#else\n"); 
    fprintf (To, "    #define __DOT__ \"");
    
    for (int i = 0; arg [1][i] != 0; i ++)
    {
                                fprintf (To, "%c", arg [1][i]);
        if (arg [1][i] == '\\') fprintf (To, "%c", arg [1][i]);    
    }
    
    fprintf (To, "\"\n");  
    
    fprintf (To, "#endif\n"); 
    
    fclose (To);   
}
