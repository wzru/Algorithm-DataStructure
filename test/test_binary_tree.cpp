/*
	Programed by ShaunWang
	Created on 2019.1.5
	Last modified on 2020.1.5
*/
#include "../data_structure/binary_tree.hpp"
#include <iostream>

using namespace std;

const char *filename0 = "tree.txt";//保存主树的文件
const char *filename1 = "insert.txt";//保存待插入树的文件

int visit (TElemType e) { printf ("%2c", e); return TRUE; }

inline void PrintInformation()
{
    system ("cls");
    system ("color 0C");
    printf ("----------------------------------------------  \n");
    cout << "0 Exit" << endl
         << "1 Init Binary Tree" << endl
         << "2 Destroy Binary Tree" << endl
         << "3 Create Binary Tree" << endl
         << "4 Clear Binary Tree" << endl
         << "5 Empty Binary Tree" << endl
         << "6 Depth Binary Tree" << endl
         << "7 Root" << endl
         << "8 Value" << endl
         << "9 Assign" << endl
         << "10 Parent" << endl
         << "11 Left Child" << endl
         << "12 Right Child" << endl
         << "13 Left Sibling" << endl
         << "14 Right Sibling" << endl
         << "15 Insert Child" << endl
         << "16 Delete Child" << endl
         << "17 Preorder Traverse " << endl
         << "18 Inorder Traverse" << endl
         << "19 Postorder Traverse" << endl
         << "20 Levelorder Traverse" << endl
         << "21 Save to File" << endl;
    cout << "Press a number(0 - 21) that you want to do: ";
}

int main (void)
{
    BinaryTree T = NULL, q = NULL, T1 = NULL;
    int op = 1, t = 0, e = 0, i = 0, n = 1, j, LR;
    ElemType w;
    char *definition;
    char c;
    while (op)
    {
        PrintInformation();
        scanf ("%d", &op);
        switch (op)
        {
        case 1:
            t = 0;  //flag
            if (T == NULL)
            {
                t = 1;
            }
            if (t && InitBinaryTree (T) == OK)
            {
                printf ("Binary Tree has constructed SUCCESSFULLY!\n");
            }
            else
            {
                printf ("Binary Tree constructed FAILED!\n");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 2:
            if (T != NULL)
            {
                DestroyBinaryTree (T);
                T = NULL;  //表示Binary Tree NOT EXISTED!
                i = 0, n = 1;  //清空构造且重新计Key
                printf ("Binary Tree has been DESTROYED!");
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 3:
            if (T != NULL)
            {
                if (!i)
                {
                    FILE *fp;  //将文件中已经构造好的树读入
                    if ( (fp = fopen (filename0, "r")) == NULL)
                    {
                        printf ("File open error!\n ");
                    }
                    else
                    {
                        i = CreateBinaryTree (T->lchild, n, fp);
                        printf ("Binary Tree init SUCCESSFULLY!");
                        fclose (fp);
                    }
                }
                else
                {
                    printf ("Binary Tree init SUCESSFULLY!\n");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 4:
            if (T != NULL)
            {
                ClearBinaryTree (T->lchild); //将根结点作为参数
                T->lchild = NULL;  //置空树
                i = 0, n = 1;  //清空构造且重新计Key
                printf ("Binary Tree has been clear!");
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 5:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("Binary Tree is EMPTY!\n");
                }
                else
                {
                    printf ("NOT EMPTY!\n");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 6:
            if (T != NULL)
            {
                printf ("Depth : %d", BinaryTreeDepth (T->lchild));
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 7:
            if (T != NULL)
            {
                q = Root (T);
                printf ("Root : %c", q->others);
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 8:
            if (T != NULL)
            {
                int cur_e, j;
                c = ' ';  //赋初值
                printf ("Please input the key (key is from 1):");
                scanf ("%d", &cur_e);
                if (cur_e > 0 && cur_e < n)
                {
                    Value (T->lchild, cur_e, c);
                    if (c == ' ')
                    {
                        printf ("NOT FOUND!");
                    }
                    else
                    {
                        printf ("\nKey : %d，结点为%c", cur_e, c);
                    }
                }
                else
                {
                    printf ("INVALID!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 9:
            if (T != NULL)
            {
                TElemType value;
                PreOrderTraverse (T->lchild, visit); //输出此时树中元素
                printf ("\nAbove is the Tree, please input the key of which you want to assign:");
                scanf ("%d", &w);
                getchar();  //吸收回车
                printf ("Please input the value：");
                scanf ("%c", &value);
                Assign (T, w, value);
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 10:
            if (T != NULL)
            {
                printf ("Please input the key：");
                scanf ("%d", &w);
                Parent (T, w, q);
                if (q)
                {
                    //此时q指向所查找的结点上
                    printf ("\nParent : %c", q->others);
                    q = NULL;//重置
                }
                else
                {
                    printf ("\nNOT FOUND!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 11:
            if (T != NULL)
            {
                printf ("Please input the key：");
                scanf ("%d", &w);
                LeftChild (T, w, q);
                if (q)
                {
                    //此时q指向所查找的结点上
                    printf ("Left Child : %c", q->others);
                    q = NULL;//重置
                }
                else
                {
                    printf ("\nNOT FOUND!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 12:
            if (T != NULL)
            {
                printf ("Please input the key：");
                scanf ("%d", &w);
                RightChild (T, w, q);
                if (q)
                {
                    //此时q指向所查找的结点上
                    printf ("Right Child : %c", q->others);
                    q = NULL;//重置
                }
                else
                {
                    printf ("\nNOT FOUND!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 13:
            if (T != NULL)
            {
                printf ("Please input the key of which you want to find its Left Sibiling：");
                scanf ("%d", &w);
                int j = OVERFLOW; //flag
                j = LeftSibling (T, w, q);
                if (j == TRUE)
                {
                    printf ("Left Sibiling : %c", q->others);
                    q = NULL;  //重置
                }
                else if (j == FALSE)
                { printf ("NOT FOUND"); }
                else
                {
                    printf ("Left Sibiling NOT FOUND!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 14:
            if (T != NULL)
            {
                printf ("Please input the key of which you want to find its Right Sibiling：");
                scanf ("%d", &w);
                int j = OVERFLOW;  //flag
                j = RightSibling (T, w, q);
                if (j == TRUE)
                {
                    printf ("Right Sibiling : %c", q->others);
                    q = NULL;  //重置
                }
                else if (j == FALSE)
                {
                    printf ("NOT FOUND!");
                }
                else
                {
                    printf ("Right Sibiling NOT FOUND!");
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 15:
            if (T != NULL)
            {
                printf ("Please input the index of the inserted position：");
                getchar();  //吸收回车
                scanf ("%c", &c);
                getchar();  //吸收回车
                Search (T, c, q);
                FILE *fp;
                if ( (fp = fopen (filename1, "r")) == NULL)
                {
                    printf ("File open error!\n ");
                }
                else
                {
                    CreateBinaryTree (T1, n, fp);
                    printf ("Init SUCESSFULLY!\n");
                    fclose (fp);
                }
                printf ("Please input 0(left) or 1(right)：");
                scanf ("%d", &LR);
                if (InsertChild (T, q, LR, T1))
                {
                    printf ("Insert SUCESSFULLY!");
                }
                else
                {
                    printf ("Insert FAILED!");
                }
                q = NULL;  //置空以方便后续使用
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 16:
            if (T != NULL)
            {
                printf ("Please input the Node that you want to delete its subtree：");
                getchar();  //吸收回车
                scanf ("%c", &c);
                getchar();  //吸收回车
                Search (T, c, q);
                printf ("Please input 0(left) or 1(right)：");
                scanf ("%d", &LR);
                if (DeleteChild (T, q, LR))
                {
                    printf ("Deleted SUCESSFULLY!");
                }
                else
                {
                    printf ("Deleted FAILED!");
                }
                q = NULL;  //置空以方便后续使用
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 17:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("The Binary Tree is EMPTY!\n");
                }
                else
                {
                    printf ("Preorder：\n");
                    PreOrderTraverse (T->lchild, visit);
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 18:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("The Binary Tree is EMPTY!\n");
                }
                else
                {
                    printf ("Inorder：\n");
                    InOrderTraverse (T->lchild, visit);
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 19:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("The Binary Tree is EMPTY!\n");
                }
                else
                {
                    printf ("Postorder：\n");
                    PostOrderTraverse (T->lchild, visit);
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 20:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("The Binary Tree is EMPTY!\n");
                }
                else
                {
                    printf ("Levelorder：\n");
                    LevelOrderTraverse (T, visit);
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 21:
            if (T != NULL)
            {
                if (BinaryTreeEmpty (T))
                {
                    printf ("The Binary Tree is EMPTY!\n");
                }
                else
                {
                    FILE *fp;
                    if ( (fp = fopen (filename0, "w")) == NULL)
                    {
                        printf ("File open error!\n ");
                    }
                    else
                    {
                        SaveData (T->lchild, fp);
                        printf ("Save SUCCESSFULLY!");
                        fclose (fp);
                    }
                }
            }
            else
            {
                printf ("Binary Tree NOT EXISTED!");
            }
            getchar();
            printf ("\nPress ENTER to RETURN...");
            getchar();
            break;
        case 0:
            break;
        }
    }
    printf ("Process QUIT!\n");
    return 0;
}
