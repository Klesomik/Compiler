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

struct newNode //��������� ����
{
    int Descriptor; //���������� �����, ����������� �� ���
     
    double Value;   //��������        

    newNode ();
};

newNode::newNode () :
    Descriptor (N_NULL)
{}        

//==============================================================================

class newTree //������ �������� ������(����� �������) 
{
    private:
    int Size_;              //������         
    std::vector <newNode> Data_; //����
      
    public:
    newTree ();
    
    bool OK ();   //�������, �� �� � ������� � �������
    void Dump (); //�� ������������ (�� ������� �������� ���������� ;))
    
    int Size (); //���������� ������
    int Size (int NewSize); //������������� ������
    
    int GetL (int Me); //���������� ������ ����
    int GetR (int Me); //���������� ������� ����
    int GetP (int Me); //���������� ��������
    
    newNode& operator [] (int i); //���������� ������ �� ����             
};

//------------------------------------------------------------------------------

newTree::newTree () :
    Size_ (0)                 
{}
    
bool newTree::OK ()
{
    if (Size_ < 0) return false; //� ��� ����� ������� ������. ������������ ��������� ������ - ������������� ������
    
    return true;     
}
    
int newTree::Size ()
{
    return Size_; //��, �� - � �� ��������� ��� (��. ����) )
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
    if (!OK ()) throw "All BAD!"; //���������, �� �� � �������.     
         
    if (i >= Size_) //����� ����� ������. ���� ������ ��� �����, �������� ������. ����� ������� ���� �������������, ���� �������� �������� �����!
    {
        Size_ = i + 1;  
        Data_.resize (Size_);      
    }         
    
    return Data_ [i];
}

#endif
