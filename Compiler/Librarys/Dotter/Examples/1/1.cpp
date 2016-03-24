#include "Dotter.h"

int main ()
{
    dtBegin ("Example1.dot"); //Начало dot графа 
    
    dtNode (0, "Node number 0!"); //Рисуем узел 0 с надписью "Node number 0"
    dtNode (1, "Node number 1!"); //Рисуем узел 1 с надписью "Node number 1"
    dtNode (2, "Node number 2!"); //Рисуем узел 2 с надписью "Node number 2"
    dtNode (3, "Node number 3!"); //Рисуем узел 3 с надписью "Node number 3"
    
    dtLink (0, 1, "Link from 0 to 1!"); //Рисуем связь узла 0 с узлом 1
    dtLink (0, 2, "Link from 0 to 2!"); //Рисуем связь узла 0 с узлом 2
    
    dtLink (1, 3, "Link from 1 to 3!"); //Рисуем связь узла 1 с узлом 3
    dtLink (2, 3, "Link from 2 to 3!"); //Рисуем связь узла 2 с узлом 3
    
    dtLink (3, 0, "Link from 3 to 0!"); //Рисуем связь узла 3 с узлом 0
    
    dtEnd (); //Конец dot графа
    
    dtRender ("Example1.dot"); //Делаем из файла картинку 
}
