#ifndef TREEPRINTER__
#define TREEPRINTER__

#include "Dotter.h"
#include "Tree.h"

//==============================================================================

void PrintNode (int i, newNode Node); //������ ��� ������ dotter ���� 

//==============================================================================

void PrintTree (newTree& Tree, bool Real = false); //������ � dotter ������. Real = false, �. �. Real �� �������.

//==============================================================================

void PrintNode (int i, newNode Node)
{
    dtNodeStyle ().shape ("box")              //�� ��������� ����� - �������. 
                  .style ("rounded, filled"); //�� ��������� ����� - �����������, ���������.

    char Title [30] = ""; //����� 

    switch (Node.Descriptor) //��������� �������� ����������� � ������������� ����� � �����
    {
        case (N_NULL):
        {
            dtNodeStyle ().style ("diagonals"); 
             
            sprintf (Title, "%d\nNULL", i);
             
            break;     
        }
        
        case (N_NUM):
        {
            dtNodeStyle ().fontcolor ("darkgreen") //��� �������� ����� ���� ��������� �. �. ���������. �������! 
                          .color     ("darkgreen") //��� �������� ����� ���� ��������� �. �. ���������. �������!
                          .fillcolor ("#98FF66");  //��� �������� ����� ���� ��������� �. �. ���������. �������!
            
            sprintf (Title, "#%d\n%lg", i, Node.Value);
             
            break;     
        }
        
        case (N_MUL):
        {
            dtNodeStyle ().fontcolor ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������! 
                          .color     ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������!
                          .fillcolor ("#FFCCC9"); //��� �������� ����� ���� ��������� �. �. ���������. �������! 
             
            sprintf (Title, "#%d\n*", i);
             
            break;     
        }
        case (N_DIV):
        {
            dtNodeStyle ().fontcolor ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������! 
                          .color     ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������!
                          .fillcolor ("#FFCCC9"); //��� �������� ����� ���� ��������� �. �. ���������. �������! 
            
            sprintf (Title, "#%d\n/", i);
             
            break;     
        }
        case (N_SUM):
        {
            dtNodeStyle ().fontcolor ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������! 
                          .color     ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������!
                          .fillcolor ("#FFCCC9"); //��� �������� ����� ���� ��������� �. �. ���������. �������! 
             
            sprintf (Title, "#%d\n+", i);
             
            break;     
        }
        case (N_SUB):
        {
            dtNodeStyle ().fontcolor ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������! 
                          .color     ("red")      //��� �������� ����� ���� ��������� �. �. ���������. �������!
                          .fillcolor ("#FFCCC9"); //��� �������� ����� ���� ��������� �. �. ���������. �������! 
             
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
    
    dtNode (i, Title); //������ ����
}

//==============================================================================

void PrintTree (newTree& Tree, bool Real)
{
    for (int i = 0; i < Tree.Size (); i ++)
    {
        if (Real || Tree [i].Descriptor != N_NULL) PrintNode (i, Tree[i]);
        
        if (Tree.GetL (i) < Tree.Size () && (Real || Tree[Tree.GetL (i)].Descriptor != N_NULL) && (Real || Tree [i].Descriptor != N_NULL)) dtLink (i, Tree.GetL (i)); //��������� ���� � ����� �������
        if (Tree.GetR (i) < Tree.Size () && (Real || Tree[Tree.GetR (i)].Descriptor != N_NULL) && (Real || Tree [i].Descriptor != N_NULL)) dtLink (i, Tree.GetR (i)); //��������� ���� � ������ ������� 
    }    
}

#endif
