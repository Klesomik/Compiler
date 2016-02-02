#include "Dotter.h"

int main ()
{
    dtBegin ("Example2.dot"); //Начало dot графа 
    
    dtNodeStyle ().shape    ("tab")     //Меняем форму на tab
                  .color    ("yellow")  //Меняем цвет на yellow
                  .fillcolor("red")     //Меняем цвет заливки на red 
                  .style    ("filled"); //Меняем стиль на filled 
    
    dtNode (0, "There is writen truth!"); //Рисуем узел 0
    
    dtNodeStyle ().shape("folder")      //Меняем форму на folder
                  .color("aquamarine4") //Меняем цвет на aquamarine4
                  .fillcolor("violet"); //Меняем цвет заливки на violet
    
    dtNode (1, "There is written lies!"); //Рисуем узел 1
    
    dtNodeStyle ().shape     ("component") //Меняем форму на component
                  .color     ("blue")      //Меняем цвет на blue
                  .fillcolor ("lightblue") //Меняем цвет заливки на green
                  .style     ("filled");   //Меняем стиль на filled
    
    dtNode (2, "Choose your way!"); //Рисуем узел 2
    
    dtLinkStyle ().style ("dashed"); //Меняем стиль на dashed
    
    dtLink (1, 0); //Рисуем связь узла 1 с 0
    dtLink (0, 1); //Рисуем связь узла 0 с 1
    
    newDotLinkStyle ChooseWaysLink; //Создаём структуру с описанием стиля связи
    
    dtLinkStyle ().style ("bold") //Меняем стиль на bold
                  .color ("gold"); //Меняем цвет на gold
    
    dtLink (2, 0, "way 1"); //Рисуем связь узла 2 с 0
    dtLink (2, 1, "way 2"); //Рисуем связь узла 2 с 1
    
    dtEnd (); //Конец dot графа
    
    dtRender ("Example2.dot"); //Делаем из файла картинку 
}
