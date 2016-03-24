#include "Dotter.h"

int main ()
{
    dtBegin ("Example1.dot"); //������ dot ����� 
    
    dtNode (0, "Node number 0!"); //������ ���� 0 � �������� "Node number 0"
    dtNode (1, "Node number 1!"); //������ ���� 1 � �������� "Node number 1"
    dtNode (2, "Node number 2!"); //������ ���� 2 � �������� "Node number 2"
    dtNode (3, "Node number 3!"); //������ ���� 3 � �������� "Node number 3"
    
    dtLink (0, 1, "Link from 0 to 1!"); //������ ����� ���� 0 � ����� 1
    dtLink (0, 2, "Link from 0 to 2!"); //������ ����� ���� 0 � ����� 2
    
    dtLink (1, 3, "Link from 1 to 3!"); //������ ����� ���� 1 � ����� 3
    dtLink (2, 3, "Link from 2 to 3!"); //������ ����� ���� 2 � ����� 3
    
    dtLink (3, 0, "Link from 3 to 0!"); //������ ����� ���� 3 � ����� 0
    
    dtEnd (); //����� dot �����
    
    dtRender ("Example1.dot"); //������ �� ����� �������� 
}
