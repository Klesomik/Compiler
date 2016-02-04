#ifndef TREE__
#define TREE__

#include "vector"

//==============================================================================

enum NodeDescriptors
{
    N_NULL = -1, 
    
    N_OB = 5,
    N_CB = 6,
     
    N_NUM = 0,
    
    N_MUL = 1,
    N_DIV = 2,
    
    N_SUM = 3,
    N_SUB = 4     
};

struct newNode //Структура узла
{
    int Descriptor; //Уникальное число, указывающее на тип
     
    double Value;   //Значение        

    newNode ();
};

newNode::newNode () :
    Descriptor (N_NULL)
{}        

//==============================================================================

class newTree //Полное бинарное дерево(самое простое) 
{
    private:
    int Size_;              //Размер         
    std::vector <newNode> Data_; //Дата
      
    public:
    newTree ();
    
    bool OK ();   //Говорит, всё ли с деревом в порядке
    void Dump (); //Не используется (мы сделаем отдельно визуальный ;))
    
    int Size (); //Возвращает размер
    int Size (int NewSize); //Устанавливает размер
    
    int GetL (int Me); //Возвращает левого сына
    int GetR (int Me); //Возвращает правого сына
    int GetP (int Me); //Возвращает родителя
    
    newNode& operator [] (int i); //Возвращает ссылку на узел             
};

//------------------------------------------------------------------------------

newTree::newTree () :
    Size_ (0)                 
{}
    
bool newTree::OK ()
{
    if (Size_ < 0) return false; //У нас самое простое дерево. Единственная возможная ошибка - отрицательный размер
    
    return true;     
}
    
int newTree::Size ()
{
    return Size_; //Да, да - я не обманывал Вас (см. Выше) )
}    
    
int newTree::Size (int NewSize)
{
    Size_ = NewSize;    
}    
    
int newTree::GetL (int Me)
{
    return 2 * Me + 1;    
}
int newTree::GetR (int Me)
{
    return 2 * Me + 2;    
}
int newTree::GetP (int Me)
{
    return (Me - 1) / 2;    
}
    
newNode& newTree::operator [] (int i)
{
    if (!OK ()) throw "All BAD!"; //Проверяем, всё ли в порядке.     
         
    if (i >= Size_) //Самый тупой способ. Если больше или равно, выделить память. Можно словить кучу неприятностей, если случайно передать мусор!
    {
        Size_ = i + 1;  
        Data_.resize (Size_);      
    }         
    
    return Data_ [i];
}

#endif
