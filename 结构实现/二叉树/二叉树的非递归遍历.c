#include <stdio.h>
#include <stdlib.h>
#define ELEMENTTYPE PtrToNode
#define YES 1
#define NO -1
#define MAXSIZE 100
/**
 *  abc--de-g--f---
 *  先序：abcdefg
 *  中序：cbegdfa
 *  后序: cgefdba
 */

/**
 *  树结点的定义
 */
typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinTree;
struct TreeNode
{
    char data; // 结点数据
    BinTree left; // 指向左子树
    BinTree right; // 指向右子树
    int flag; // 访问标志，方便后序遍历
};

/**
 *  栈结点的定义
 */
struct StackNode
{
    ELEMENTTYPE *data; // 存储元素的数组指针
    int top; // 栈顶指针
    int maxSize; // 堆栈最大容量
};
typedef struct StackNode *Stack;

/**
 *  为方便后序遍历，创建一记录结点访问次数的结构体
 *
 */

/******************** 堆栈函数开始 ********************/
// Stack Create
Stack CreateStack(int maxSize)
{
    Stack s = (Stack)malloc(sizeof(struct StackNode));
    s->data = (ELEMENTTYPE *)malloc(maxSize *sizeof(ELEMENTTYPE));
    s->top = -1;
    s->maxSize = maxSize;
    return s;
}

int IsFull(Stack s)
{
    return (s->top == s->maxSize-1);
}

int Push(Stack s, ELEMENTTYPE x)
{
    if (IsFull(s))
        return 0;
    s->data[++(s->top)] = x;
    return 1;
}

int IsEmpty(Stack s)
{
    return (s->top == -1);
}

ELEMENTTYPE Pop(Stack s)
{
    if (IsEmpty(s))
        return NULL;
    return s->data[(s->top)--];
}

ELEMENTTYPE Top(Stack s)
{
    if (IsEmpty(s))
        return NULL;
    return s->data[(s->top)];
}
/******************** 堆栈函数结束 ********************/

/******************** 二叉树函数 ********************/
/**
 *  先序次序输入二叉树的结点的值，’-‘字符表示空树，创建一个二叉树
 */
BinTree binTreeCreate()
{
    BinTree t;
    char x;
    scanf("%c", &x);

    if ('-' == x)
        t = NULL;
    else
    {
        t = (BinTree)malloc(sizeof(struct TreeNode));
        t->data = x;
        t->flag = 0;
        t->left = binTreeCreate(t->left);
        t->right = binTreeCreate(t->right);
    }
    return t;
}

void binTreePreOrderTraversal(BinTree T)
{
    // 创建并初始化堆栈S
    Stack s = CreateStack(MAXSIZE);
    
    while (T || !IsEmpty(s))
    {
        while (T)
        {
            printf("%c ", T->data);
            Push(s, T);
            T = T->left;
        }
        if (!IsEmpty(s)) // 栈元素不空
        {
            T = Pop(s);
            T = T->right;
        }
    }
}

void binTreeInOrderTraversal(BinTree T)
{
    // 创建并初始化堆栈S
    Stack s = CreateStack(MAXSIZE);
    
    while (T || !IsEmpty(s))
    {
        while (T)
        {
            Push(s, T);
            T = T->left;
        }
        if (!IsEmpty(s))
        {
            T = Pop(s);
            printf("%c ", T->data);
            T = T->right;
        }
    }
    
}

void binTreePostOrderTraversal(BinTree T)
{
    // 创建并初始化堆栈S
    Stack s = CreateStack(MAXSIZE);
    while (T || !IsEmpty(s))
    {
        while (T && T->flag==0)
        {
            T->flag++; // 该结点第一次访问，将其入栈
            Push(s, T);
            T = T->left;
        }
        if (!IsEmpty(s))
        {
            T = Top(s);
            if (T->flag == 2) // 后序遍历，每个结点基本上是第三次访问
            {
                T = Pop(s);  // 该结点第三次遇到
                printf("%c ", T->data);
                T = Top(s);
            }
            else
            {
                T->flag++; // 该结点第二次遇到，此时结点在栈中，但不出栈
                T = T->right;
            }
        }
    }
}

int main()
{
    BinTree t = binTreeCreate();
    
    binTreePreOrderTraversal(t);
    printf("\n");
    
    binTreeInOrderTraversal(t);
    printf("\n");
    
    binTreePostOrderTraversal(t);
    printf("\n");
    return 0;
}
