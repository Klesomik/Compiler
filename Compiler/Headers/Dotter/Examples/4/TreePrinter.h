#ifndef TREEPRINTER__
#define TREEPRINTER__

#include "Dotter.h"
#include "Tree.h"

//==============================================================================

void PrintNode (int i, newNode Node); //Рисует при помощи dotter узел 

//==============================================================================

void PrintTree (newTree& Tree, bool Real = false); //Рисует в dotter дерево. Real = false, т. к. Real не красиво.

//==============================================================================

void PrintNode (int i, newNode Node)
{
    dtNodeStyle ().shape ("box")              //По умолчанию форма - коробка. 
                  .style ("rounded, filled"); //По умолчанию стиль - заполненный, скруглёный.

    char Title [30] = ""; //Текст 

    switch (Node.Descriptor) //Разбираем значения дескриптора и устанавливаем стиль и тайтл
    {
        case (N_NULL):
        {
            dtNodeStyle ().style ("diagonals"); 
             
            sprintf (Title, "%d\nNULL", i);
             
            break;     
        }
        
        case (N_NUM):
        {
            dtNodeStyle ().fontcolor ("darkgreen") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
                          .color     ("darkgreen") //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#98FF66");  //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
            
            sprintf (Title, "#%d\n%lg", i, Node.Value);
             
            break;     
        }
        
        case (N_MUL):
        {
            dtNodeStyle ().fontcolor ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
                          .color     ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#FFCCC9"); //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
             
            sprintf (Title, "#%d\n*", i);
             
            break;     
        }
        case (N_DIV):
        {
            dtNodeStyle ().fontcolor ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
                          .color     ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#FFCCC9"); //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
            
            sprintf (Title, "#%d\n/", i);
             
            break;     
        }
        case (N_SUM):
        {
            dtNodeStyle ().fontcolor ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
                          .color     ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#FFCCC9"); //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
             
            sprintf (Title, "#%d\n+", i);
             
            break;     
        }
        case (N_SUB):
        {
            dtNodeStyle ().fontcolor ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
                          .color     ("red")      //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо!
                          .fillcolor ("#FFCCC9"); //Эти чудесные цвета были подобраны И. Р. Дединским. Спасибо! 
             
            sprintf (Title, "#%d\n-", i);
             
            break;     
        }
        
        default:
        {
            dtNodeStyle ().shape ("egg")
                          .color ("yellow")
                          .style ("filled");
                             
            sprintf (Title, "%d\nError! Descriptor = %d", i, Node.Descriptor);
             
            break;     
        }            
    }
    
    dtNode (i, Title); //Рисуем узел
}

//==============================================================================

void PrintTree (newTree& Tree, bool Real)
{
    for (int i = 0; i < Tree.Size (); i ++)
    {
        if (Real || Tree [i].Descriptor != N_NULL) PrintNode (i, Tree[i]);
        
        if (Tree.GetL (i) < Tree.Size () && (Real || Tree[Tree.GetL (i)].Descriptor != N_NULL) && (Real || Tree [i].Descriptor != N_NULL)) dtLink (i, Tree.GetL (i)); //Соединяем узел с левым ребёнком
        if (Tree.GetR (i) < Tree.Size () && (Real || Tree[Tree.GetR (i)].Descriptor != N_NULL) && (Real || Tree [i].Descriptor != N_NULL)) dtLink (i, Tree.GetR (i)); //Соединяем узел с правым ребёнком 
    }    
}

#endif
