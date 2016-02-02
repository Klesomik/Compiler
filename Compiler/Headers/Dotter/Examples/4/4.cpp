#include "Tree.h"
#include "TreePrinter.h"
#include "CreateTree.h"

int main ()
{
    try
    {
        int Size = 0; 
        std::vector <newNode> Program;
        
        printf ("This program creates instance tree and calculate result.\nPlease, put instance:");
        
        std::vector <char> Instance;
        for (int i = 0; true; i ++)
        {
            Instance.resize (i + 1);  
            scanf ("%c", &Instance [i]);
            
            if (Instance [i] == '\n' || Instance [i] == '\r' || Instance [i] == '\0' || Instance [i] == '\r')
            {
                Instance [i] = 0;
                         
                break;
            }    
        }
        
        ScanfProgram (&Instance[0], Program, &Size);
        
        newTree Tree;
    
        CreateTree (Tree, &Program [0], Size);
    
        dtBegin ("TreeDump.dot");
        
        PrintTree (Tree);
        
        fprintf (DotterSystem::CurrentFile, "    subgraph clusterTitle\n"); //������ �������. ��� ������ ���������� � cluster, ����� ������ �� ����������.
        fprintf (DotterSystem::CurrentFile, "    {\n");
        fprintf (DotterSystem::CurrentFile, "        shape=\"rect\";\n");     //����� = �������������
        fprintf (DotterSystem::CurrentFile, "        style=\"filled\";\n");   //����� = � ��������
        fprintf (DotterSystem::CurrentFile, "        \n");
        fprintf (DotterSystem::CurrentFile, "        color=\"black\";\n");    //���� = �����
        fprintf (DotterSystem::CurrentFile, "        fillcolor=\"gray\";\n"); //���� ������� = �����
        fprintf (DotterSystem::CurrentFile, "        \n");
        fprintf (DotterSystem::CurrentFile, "        fontsize=16;\n");        //������ ������ = 16 ��. 
        fprintf (DotterSystem::CurrentFile, "        fontcolor=\"red\"\n");   //���� ������ = �������
        fprintf (DotterSystem::CurrentFile, "        \n");
        fprintf (DotterSystem::CurrentFile, "        label=\"Info\";\n");     //����� = Info
        fprintf (DotterSystem::CurrentFile, "        \n");
        fprintf (DotterSystem::CurrentFile, "        InstanceNode [shape=\"rect\", style=\"filled\", color=black, fillcolor=lightgray, label=\"%s\\nResult=%lg\"];\n", &Instance [0], GetResult(Tree)); //����� ��������� � ��������� (��. Dotguide.pdf)
        fprintf (DotterSystem::CurrentFile, "    }\n");
        
        dtEnd ();
        
        dtRender ("TreeDump.dot");

        system ("pause");
    }
    
    catch (const char Error [])
    {
        printf ("Error! Message: %s\n", Error);
        
        system ("pause");
    }
    
    catch (...)
    {
        printf ("Error!");
        
        system ("pause");      
    }
}
