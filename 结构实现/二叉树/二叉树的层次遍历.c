#include <stdio.h>
#include <stdlib.h>
#define ElementType PtrToNode
#define YES 1
#define NO 0

/*******树的定义*******/
typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinTree;
/**
 *  树结点的定义
 */
struct TreeNode
{
    char data; // 结点数据
    BinTree left; // 指向左子树
    BinTree right; // 指向右子树
};

/*******队列结点的定义*******/
typedef int Position;
struct QNode
{
    ElementType *data; // 存储元素的数组
    Position rear; // 队列的尾指针
    Position front; // 队列的头指针
    int maxSize; // 队列的最大容量
};
typedef struct QNode *Queue;

Queue CreateQueue(int maxSize)
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->data = (ElementType *)malloc(sizeof(ElementType));
    q->front = q->rear = 0;
    q->maxSize = maxSize;
    return q;
}

int IsFull(Queue q)
{
    return ((q->rear+1)%q->maxSize == q->front);
}

int AddQ(Queue q, ElementType x)
{
    if (IsFull(q))
        return NO;
    q->rear = (q->rear+1)%q->maxSize;
    q->data[q->rear] = x;
    return YES;
}

int IsEmpty(Queue q)
{
    return (q->front == q->rear);
}

ElementType DeleteQ(Queue q)
{
    if (IsEmpty(q))
    {
        printf("队列空\n");
        return NO;
    }
    else
    {
        q->front = (q->front+1)%q->maxSize;
        return q->data[q->front];
    }
}

/**
 *  abc--de-g--f---
 *  先序：abcdefg
 *  中序：cbegdfa
 *  后序: cgefdba
 */

/**
 *  先序次序输入二叉树的结点的值，’-‘字符表示空树，创建一个二叉树
 */
BinTree binTreeCreate()
{
    BinTree t;
    char temp;
    scanf("%c", &temp);

    if ('-' == temp)
        t = NULL;
    else
    {
        t = (BinTree)malloc(sizeof(struct TreeNode));
        t->data = temp;
        t->left = binTreeCreate(t->left);
        t->right = binTreeCreate(t->right);
    }
    return t;
}

void binTreeLevelorderTraversal(BinTree T) // 层次遍历
{
    int i = 0;
    Queue q;
    PtrToNode cur;
    if(T == NULL) return;
    q = CreateQueue(10);
    AddQ(q, T);
    while(!IsEmpty(q))
    {
        cur = DeleteQ(q);
        if(i++ != 0)
            printf("->");
        printf("%c", cur->data);
        if(cur->left)
            AddQ(q, cur->left);
        if(cur->right)
            AddQ(q, cur->right);
    }
}

int main()
{
    BinTree t = binTreeCreate();
    binTreeLevelorderTraversal(t);
    return 0;
}
