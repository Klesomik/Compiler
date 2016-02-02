#include "Dotter.h"

int main ()
{
    dtBegin ("Example2.dot"); //������ dot ����� 
    
    dtNodeStyle ().shape    ("tab")     //������ ����� �� tab
                  .color    ("yellow")  //������ ���� �� yellow
                  .fillcolor("red")     //������ ���� ������� �� red 
                  .style    ("filled"); //������ ����� �� filled 
    
    dtNode (0, "There is writen truth!"); //������ ���� 0
    
    dtNodeStyle ().shape("folder")      //������ ����� �� folder
                  .color("aquamarine4") //������ ���� �� aquamarine4
                  .fillcolor("violet"); //������ ���� ������� �� violet
    
    dtNode (1, "There is written lies!"); //������ ���� 1
    
    dtNodeStyle ().shape     ("component") //������ ����� �� component
                  .color     ("blue")      //������ ���� �� blue
                  .fillcolor ("lightblue") //������ ���� ������� �� green
                  .style     ("filled");   //������ ����� �� filled
    
    dtNode (2, "Choose your way!"); //������ ���� 2
    
    dtLinkStyle ().style ("dashed"); //������ ����� �� dashed
    
    dtLink (1, 0); //������ ����� ���� 1 � 0
    dtLink (0, 1); //������ ����� ���� 0 � 1
    
    newDotLinkStyle ChooseWaysLink; //������ ��������� � ��������� ����� �����
    
    dtLinkStyle ().style ("bold") //������ ����� �� bold
                  .color ("gold"); //������ ���� �� gold
    
    dtLink (2, 0, "way 1"); //������ ����� ���� 2 � 0
    dtLink (2, 1, "way 2"); //������ ����� ���� 2 � 1
    
    dtEnd (); //����� dot �����
    
    dtRender ("Example2.dot"); //������ �� ����� �������� 
}
