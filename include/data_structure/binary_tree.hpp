/*
	Programed by ShaunWang
	Created on 2019.1.5
	Last modified on 2020.1.5
*/
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <cstdio>
#include <malloc.h>
#include <cstdlib>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2


typedef int status;//其是指函数结果状态代码
typedef char TElemType; //数据元素类型定义
typedef int ElemType;//标识元素类型定义

struct Node
{
    ElemType key;
    TElemType others;
    Node *lchild, *rchild;//左右孩子指针
};

typedef Node *BinaryTree;

status InitBinaryTree (BinaryTree &T);
status DestroyBinaryTree (BinaryTree &T);
status CreateBinaryTree (BinaryTree &T, int &num, FILE *fp);
status ClearBinaryTree (BinaryTree &T);
status BinaryTreeEmpty (BinaryTree T);
status BinaryTreeDepth (BinaryTree T);
BinaryTree Root (BinaryTree T) { return T->lchild; } //已知根结点位置
status Value (BinaryTree T, ElemType cur_e, TElemType &e);
status Assign (BinaryTree &T, ElemType &e, TElemType value);
status Parent (BinaryTree T, ElemType e, BinaryTree &p);
status LeftChild (BinaryTree T, ElemType e, BinaryTree &p);
status RightChild (BinaryTree T, ElemType e, BinaryTree &p);
status LeftSibling (BinaryTree T, ElemType e, BinaryTree &p);
status RightSibling (BinaryTree T, ElemType e, BinaryTree &p);
status InsertChild (BinaryTree &T, BinaryTree &p, int LR, BinaryTree c);
status DeleteChild (BinaryTree &T, BinaryTree &p, int LR);
status PreOrderTraverse (BinaryTree T, int (*Visit) (TElemType e));
status InOrderTraverse (BinaryTree T, int (*Visit) (TElemType e));
status PostOrderTraverse (BinaryTree T, int (*Visit) (TElemType e));
status LevelOrderTraverse (BinaryTree T, int (*Visit) (TElemType e));
status Search (BinaryTree T, TElemType e,
               BinaryTree &p); //查找结点的指针
status SaveData (BinaryTree T, FILE *fp);

status InitBinaryTree (BinaryTree &T)
{
    T = (BinaryTree) malloc (sizeof (Node)); //分配空间给头结点
    if (!T)
    {
        exit (OVERFLOW);    //存储分配失败
    }
    T->lchild = NULL;  //置空表
    T->rchild = NULL;  //防止指针悬挂
    return OK;
}
status BinaryTreeEmpty (BinaryTree T)
{
    if (!T->lchild)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
status CreateBinaryTree (BinaryTree &T, int &num, FILE *fp)
{
    char ch;
    fscanf (fp, "%c", &ch);
    if (ch == ' ')
    {
        T = NULL;    //是否是虚结点
    }
    else
    {
        T = (BinaryTree) malloc (sizeof (Node));
        if (!T)
        {
            exit (OVERFLOW);    //存储分配失败
        }
        T->key = num++;  //给结点编号
        T->others = ch;  //将数据元素存储
        printf ("%c\n", ch);
        CreateBinaryTree (T->lchild, num, fp);
        CreateBinaryTree (T->rchild, num, fp);
    }
    return OK;
}
status DestroyBinaryTree (BinaryTree &T)
{
    //从头结点开始递归，最后释放头结点
    if (T)
    {
        DestroyBinaryTree (T->lchild);
        DestroyBinaryTree (T->rchild);
        free (T);
    }
    return TRUE;
}
status ClearBinaryTree (BinaryTree &T)
{
    if (T)
    {
        ClearBinaryTree (T->lchild);
        ClearBinaryTree (T->rchild);
        free (T); //释放完左右子树后再释放根结点
    }
    return TRUE;
}
status BinaryTreeDepth (BinaryTree T)
{
    int d = 0, ld = 0, rd = 0;//深度
    if (T)
    {
        //从根结点出发采用递归求深度
        ld = BinaryTreeDepth (T->lchild);
        rd = BinaryTreeDepth (T->rchild);
        d = ld > rd ? ld + 1 : rd + 1;
    }
    return d;
}
status Value (BinaryTree T, ElemType cur_e, TElemType &e)
{
    if (T != NULL)
    {
        if (T->key == cur_e)
        {
            e = T->others;
            return TRUE;  //找到返回
        }
        Value (T->lchild, cur_e, e);
        Value (T->rchild, cur_e, e);
        return TRUE;
    }
    else
    {
        return FALSE;    //到叶节点为止
    }
}
status Assign (BinaryTree &T, ElemType &e, TElemType value)
{
    if (T != NULL)
    {
        if (T->key == e)
        {
            T->others = value;
            printf ("赋值成功");
            return TRUE;  //找到并修改返回成功
        }
        Assign (T->lchild, e, value);
        Assign (T->rchild, e, value);
        return TRUE;
    }
    else
    {
        return FALSE;    //到叶节点为止
    }
}
status Parent (BinaryTree T, ElemType e, BinaryTree &p)
{
    if (e == 1)
    {
        return FALSE;
    }
    if (T->lchild != NULL || T->rchild != NULL)
    {
        if (T->lchild && T->lchild->key == e)
        {
            p = T;
            return TRUE;  //找到并修改返回成功
        }
        if (T->rchild && T->rchild->key == e)
        {
            p = T;
            return TRUE;  //找到并修改返回成功
        }
        if (T->lchild)
        {
            Parent (T->lchild, e, p);    //左子树递归
        }
        if (T->rchild)
        {
            Parent (T->rchild, e, p);    //右子树递归
        }
        return TRUE;
    }
    else
    {
        return FALSE;    //到叶节点为止
    }
}
status LeftChild (BinaryTree T, ElemType e, BinaryTree &p)
{
    if (T)
    {
        if (T->lchild && T->key == e)
        {
            p = T->lchild;
            return TRUE;  //找到并修改返回成功
        }
        LeftChild (T->lchild, e, p); //左子树递归
        if (T->rchild)
        {
            LeftChild (T->rchild, e, p);    //右子树递归
        }
        return TRUE;
    }
    else
    {
        return FALSE;    //到叶节点为止
    }
}
status RightChild (BinaryTree T, ElemType e, BinaryTree &p)
{
    if (T)
    {
        if (T->rchild && T->key == e)
        {
            p = T->rchild;
            return TRUE;  //找到并修改返回成功
        }
        if (T->lchild)
        {
            RightChild (T->lchild, e, p);    //左子树递归
        }
        RightChild (T->rchild, e, p); //右子树递归
        return TRUE;
    }
    else
    {
        return FALSE;    //到叶节点为止
    }
}
status LeftSibling (BinaryTree T, ElemType e, BinaryTree &p)
{
    if (e == 1)
    {
        return OVERFLOW;    //判断根结点
    }
    Parent (T, e, p); //找其双亲结点
    if (p)
    {
        if (p->lchild && (p->lchild->key != e))
        {
            p = p->lchild;
            return TRUE;
        }
        else
        {
            return OVERFLOW;    //左兄弟不存在
        }
    }
    else
    {
        return FALSE;    //无该结点
    }
}
status RightSibling (BinaryTree T, ElemType e, BinaryTree &p)
{
    if (e == 1)
    {
        return OVERFLOW;    //判断根结点
    }
    Parent (T, e, p); //找其双亲结点
    if (p)
    {
        if (p->rchild && (p->rchild->key != e))
        {
            p = p->rchild;
            return TRUE;
        }
        else
        {
            return OVERFLOW;    //左兄弟不存在
        }
    }
    else
    {
        return FALSE;    //无该结点
    }
}
status InsertChild (BinaryTree &T, BinaryTree &p, int LR, BinaryTree c)
{
    BinaryTree s;
    if (!LR)
    {
        s = p->lchild;  //保留原位置
        p->lchild = c;  //插入
        BinaryTree t = p;
        while (t && t->rchild)
        {
            t = t->rchild;
        }  //移动指针到其空右子树
        t->rchild = s;  //将原来分离的子树插入空的右子树中
        return TRUE;
    }
    else
    {
        s = p->rchild;
        p->rchild = c;
        while (c->rchild)
        {
            c = c->rchild;
        }
        c->rchild = s;
        return TRUE;
    }
    return FALSE;
}
status DeleteChild (BinaryTree &T, BinaryTree &p, int LR)
{
    if (!LR)
    {
        ClearBinaryTree (p->lchild);
        p->lchild = NULL;
        return TRUE;
    }
    else
    {
        ClearBinaryTree (p->rchild);
        p->rchild = NULL;
        return TRUE;
    }
    return FALSE;
}
status PreOrderTraverse (BinaryTree T, int (*Visit) (TElemType e))
{
    if (T)
    {
        printf ("\nkey值为%d的结点为:", T->key);
        if (Visit (T->others))
            if (PreOrderTraverse (T->lchild, Visit))
                if (PreOrderTraverse (T->rchild, Visit))
                {
                    return OK;
                }
        return ERROR;
    }
    else
    {
        return OK;
    }
}
status InOrderTraverse (BinaryTree T, int (*Visit) (TElemType e))
{
    //中序遍历
    if (T)
    {
        InOrderTraverse (T->lchild, Visit);
        printf ("\nkey值为%d的结点为:", T->key);
        Visit (T->others);
        InOrderTraverse (T->rchild, Visit);
    }
    return TRUE;
}
status PostOrderTraverse (BinaryTree T, int (*Visit) (TElemType e))
{
    //后序遍历
    if (T)
    {
        PostOrderTraverse (T->lchild, Visit);
        PostOrderTraverse (T->rchild, Visit);
        printf ("\nkey值为%d的结点为:", T->key);
        Visit (T->others);
    }
    return TRUE;
}
status LevelOrderTraverse (BinaryTree T, int (*Visit) (TElemType e))
{
    //利用足够大的数组去实现队列进行按层遍历
    BinaryTree t[50];
    int i = 0;  //队头
    int n = 1;  //队尾
    if (T->lchild == NULL)
    {
        return TRUE;
    }
    t[i] = T->lchild;  //根结点入队
    while (i < n)  //判断队空
    {
        //进行按层遍历
        printf ("\nkey值为%d的结点为:", t[i]->key);
        Visit (t[i]->others);
        if (t[i]->lchild)
        {
            t[n++] = t[i]->lchild;
        }
        if (t[i]->rchild)
        {
            t[n++] = t[i]->rchild;
        }
        i++;
    }
    return TRUE;
}
status Search (BinaryTree T, TElemType e, BinaryTree &p)
{
    //依据输入的数据来指向对应结点
    if (T != NULL)
    {
        if (T->others == e)
        {
            //判断是否相等
            p = T;
            return TRUE;  //找到并修改返回指针
        }
        Search (T->lchild, e, p);
        Search (T->rchild, e, p);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
status SaveData (BinaryTree T, FILE *fp)
{
    //保存二叉树
    char ch;
    if (T)
    {
        ch = T->others;
        fprintf (fp, "%c", ch);
        SaveData (T->lchild, fp);
        SaveData (T->rchild, fp);
    }
    else
    {
        fprintf (fp, " ");
        return OK;
    }
    return OK;
}



#endif