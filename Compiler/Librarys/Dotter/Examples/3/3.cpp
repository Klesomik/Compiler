#include "..//..//Dotter.h"

int main ()
{
    dtBegin ("Example3.dot"); //Начало dot графа

    dtNodeStyle ().shape ("box"); //Меняем форму на box

    dtNode (0, "i = 0\n value = 1"); //Рисуем узел 0
    dtNode (1, "i = 1\n value = 3"); //Рисуем узел 1
    dtNode (2, "i = 2\n value = 9"); //Рисуем узел 2
    dtNode (3, "i = 3\n value = 5"); //Рисуем узел 3
    dtNode (4, "i = 4\n value = 6"); //Рисуем узел 4
    dtNode (5, "i = 5\n value = 4"); //Рисуем узел 5
    dtNode (6, "i = 6\n value = 4"); //Рисуем узел 6

    dtLinkStyle ().style ("dashed"); //Меняем стиль на dashed

    dtLink (0, 1); //Рисуем связь узла 0 с 1
    dtLink (0, 2); //Рисуем связь узла 0 с 2
    dtLink (0, 3); //Рисуем связь узла 0 с 3

    dtLink (3, 4); //Рисуем связь узла 3 с 4
    dtLink (3, 5); //Рисуем связь узла 3 с 5

    dtLink (5, 6); //Рисуем связь узла 5 с 6

    dtLinkStyle ().style ("bold") //Меняем стиль на bold
                  .color ("red"); //Меняем цвет на red

    dtLink (4, 6, "Error"); //Рисуем связь узла 4 с 6

    dtEnd (); //Конец dot графа

    dtRender ("Example3.dot"); //Делаем из файла картинку
}
