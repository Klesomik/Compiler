#include "Dotter.h"

int main ()
{
    dtBegin ("Logo.dot");
    
    dtNodeStyle ().shape     ("box")
                  .style     ("filled")
                  .color     ("cyan")
                  .fillcolor ("cyan");
    
    dtNode (0, "Dot");
    
    dtNodeStyle ().shape ("box")
                  .style ("filled");
    
    dtNodeStyle ().color     ("red")
                  .fillcolor ("red"); 
    dtNode (1, "D");
    
    dtNodeStyle ().color     ("salmon")
                  .fillcolor ("salmon"); 
    dtNode (2, "O");
    
    dtNodeStyle ().color     ("green")
                  .fillcolor ("green"); 
    dtNode (3, "T");
    
    dtNodeStyle ().color     ("navy")
                  .fillcolor ("navy"); 
    dtNode (4, "T");
    
    dtNodeStyle ().color     ("blueviolet")
                  .fillcolor ("blueviolet"); 
    dtNode (5, "E");
    
    dtNodeStyle ().color     ("tan")
                  .fillcolor ("tan"); 
    dtNode (6, "R");
    
    dtLinkStyle ().style ("dashed")
                  .color ("lightblue");
    
    dtLink (0, 1);
    dtLink (0, 2);
    dtLink (0, 3);
    dtLink (0, 4);
    dtLink (0, 5);
    dtLink (0, 6);
    
    dtLinkStyle ().style ("bold")
                  .color ("yellow");
    
    dtLink (1, 2);
    dtLink (2, 3);
    dtLink (3, 4);
    dtLink (4, 5);
    dtLink (5, 6);
    
    dtEnd ();
    
    dtRender ("Logo.dot");
}
