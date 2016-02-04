#ifndef CREATETREE__
#define CREATETREE__

#include "Tree.h"
#include "stdio.h"

//==============================================================================

void Cut (newTree& Tree); //Ужимает дерево

void UpBranch (newTree& Tree, int i); //Поднимает поддерево наверх

void ScanfProgram (char Instance [], std::vector <newNode>& Program, int* Size); //Преобразует Instance в программу

//==============================================================================

void CreateTree (newTree& Tree, newNode Program [], int Size); //Строит дерево

void GetM (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i); //+-
void GetS (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i); //*/
void GetN (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i); //Число

//==============================================================================

double GetResult (newTree& Tree, int i = 0); //Вычисляет результат выражения, заданного деревом

//==============================================================================

void Cut (newTree& Tree)
{
    for (int i = Tree.Size () - 1; i > 0; i --)
    {
        if (Tree [i].Descriptor == N_NULL)
        {
            Tree.Size (i);         
        }
        else
        {
            break;    
        }    
    }     
}

void UpBranch (newTree& Tree, int i)
{
    for (int From = i, To = i, Up = Tree.GetP (i); From < Tree.Size (); From = Tree.GetL (From), To = Tree.GetR (To), Up = Tree.GetL (Up))
    {
        if (To >= Tree.Size ())
        {
            memcpy (&Tree[Up], &Tree[From], sizeof (newNode) * (Tree.Size () - From));           
        
            for (int j = From; j < Tree.Size (); j ++)
            {
                Tree[j].Descriptor= N_NULL;    
            }
        }
        else
        {
            memcpy (&Tree[Up], &Tree[From], sizeof (newNode) * (To - From + 1));    
        
            for (int j = From; j < To + 1; j ++)
            {
                Tree[j].Descriptor = N_NULL;    
            }
        }    
    }
    
    Cut (Tree);      
}

void ScanfProgram (char Instance [], std::vector <newNode>& Program, int* Size)
{
    int c = 0;
    int i = 0; 
    while (true)
    {
        if (Instance [c] == '\n' || Instance [c] == '\r' || Instance [c] == '\0' || Instance [c] == '\r') break;
        if (Instance [c] == ' ')
        {
            c ++;  
            continue;
        }
        
        if (Instance [c] == '+')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_SUM; 
            
            i ++;  
            c ++;
            continue;          
        }
        if (Instance [c] == '-')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_SUB; 
            
            i ++;   
            c ++;
            continue;          
        }
        if (Instance [c] == '*')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_MUL; 
            
            i ++;   
            c ++;
            continue;          
        }
        if (Instance [c] == '/')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_DIV; 
            
            i ++;  
            c ++; 
            continue;          
        }    
        
        if (Instance [c] == '(')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_OB; 
            
            i ++;   
            c ++;
            continue;          
        }
        if (Instance [c] == ')')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_CB; 
            
            i ++;   
            c ++;
            continue;          
        }
        
        if (Instance [c] >= '0' && Instance [c] <= '9')
        {
            Program.resize (i + 1);  
            Program [i].Descriptor = N_NUM;   
            
            Program [i].Value = Instance [c] - '0';  
              
            bool Break = false;  
            while (true)
            {
                c ++;
                
                if (Instance [c] == '\n' || Instance [c] == '\r' || Instance [c] == '\0' || Instance [c] == '\r')
                {  
                    Break = true;  
                    break;
                }
                if (Instance [c] < '0' || Instance [c] > '9') break;
                
                Program [i].Value *= 10;
                Program [i].Value += Instance [c] - '0';
            }
            
            i ++;   
            
            if (Break) break;
            
            continue;          
        }
        
        throw "Unknown symbol!";
    }     
    
    *Size = i;
}

//==============================================================================

void CreateTree (newTree& Tree, newNode Program [], int Size)
{
    int Treei = 0, i = 0, PSize = Size; 
     
    GetM (Tree, Treei, Program, PSize, i);     
}

void GetM (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i)
{
    int StartI = Treei; 
     
    Treei = Tree.GetL (Treei);
    
    GetS (Tree, Treei, Program, Size, i);
    
    while (Program [i].Descriptor == N_SUM || Program [i].Descriptor == N_SUB)
    {
        Treei = Tree.GetP (Treei);  
          
        Tree [Treei] = Program [i];        
        
        i ++;
          
        Treei = Tree.GetR (Treei);  
        
        Treei = Tree.GetL (Treei);
        
        GetS (Tree, Treei, Program, Size, i);  
    }
    
    UpBranch (Tree, Treei);
    
    Treei = StartI;     
}
void GetS (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i)
{
    int StartI = Treei; 
     
    Treei = Tree.GetL (Treei);
    
    GetN (Tree, Treei, Program, Size, i);
    
    while (Program [i].Descriptor == N_MUL || Program [i].Descriptor == N_DIV)
    {
        Treei = Tree.GetP (Treei);  
          
        Tree [Treei] = Program [i];        
        
        i ++;
          
        Treei = Tree.GetR (Treei);  
        
        Treei = Tree.GetL (Treei);
        
        GetN (Tree, Treei, Program, Size, i);  
    }
    
    UpBranch (Tree, Treei);
    
    Treei = StartI;
}
void GetN (newTree& Tree, int& Treei, newNode Program [], int& Size, int& i)
{
    if (i >= Size) throw "Need Num or (";
     
    if (Program [i].Descriptor == N_NUM)
    {
        Tree[Treei] = Program [i];
        
        i ++;
        
        return;            
    }
    if (Program [i].Descriptor == N_OB)
    {
        i ++;
                
        GetM (Tree, Treei, Program, Size, i);        
        
        if (Program [i].Descriptor != N_CB) throw "Need )";        
        
        i ++;
        
        return;            
    }
    
    throw "Need Num or (";     
}

//==============================================================================

double GetResult (newTree& Tree, int i)
{ 
    if (i >= Tree.Size ()) throw "SyntaxError!!!"; //На всякий случай  
       
    if (Tree [i].Descriptor == N_NUM)
    {
        return Tree[i].Value; //Число? Вернуть значение!                       
    }
    
    if (Tree.GetR (i) >= Tree.Size ()) throw "SyntaxError!!!"; //У всех не чисел должны быть дети  
    
    if (Tree [i].Descriptor == N_SUM)
    {
        return GetResult (Tree, Tree.GetL (i)) + GetResult (Tree, Tree.GetR (i));    
    }
    if (Tree [i].Descriptor == N_SUB)
    {
        return GetResult (Tree, Tree.GetL (i)) - GetResult (Tree, Tree.GetR (i));    
    }
    if (Tree [i].Descriptor == N_MUL)
    {
        return GetResult (Tree, Tree.GetL (i)) * GetResult (Tree, Tree.GetR (i));    
    }
    if (Tree [i].Descriptor == N_DIV)
    {
        return GetResult (Tree, Tree.GetL (i)) / GetResult (Tree, Tree.GetR (i));    
    }
    
    throw "Unknown comand";       
}

#endif
