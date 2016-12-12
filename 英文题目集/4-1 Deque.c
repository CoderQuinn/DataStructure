#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};

Deque CreateDeque()
{
    Deque d;
    PtrToNode header;
    
    d = (Deque)malloc(sizeof(struct DequeRecord));
    header = (PtrToNode)malloc(sizeof(struct Node));
    header->Next = NULL;
    header->Last = NULL;
    d->Front =header;
    d->Rear = header;
    
    return d;
}

// 要考虑: 1.空的情况 2.只有一个结点 3.一般情况
int Push( ElementType X, Deque D )
{
    PtrToNode tmp = (PtrToNode)malloc(sizeof(struct Node));
    
    if (!tmp) // 结点申请失败
        return 0;
    tmp->Element = X;
    tmp->Next = NULL;
    tmp->Last = NULL;
    
    // 双端队列为空
    if (D->Front == D->Rear)
    {
        D->Front->Next = tmp;
        tmp->Last = D->Front;
        D->Rear = tmp;
    }
    else // 不为空的一般情况
    {
        tmp->Next = D->Front->Next;
        D->Front->Next->Last = tmp;
        D->Front->Next = tmp;
        tmp->Last = D->Front;
    }
    
    return 1;
}

ElementType Pop( Deque D )
{
    ElementType ret;
    PtrToNode tmp;
    
    // 队列为空
    if (D->Front == D->Rear)
        return ERROR;
    
    tmp = D->Front->Next;
    
    // 只有一个结点
    if (D->Front->Next == D->Rear)
    {
        D->Rear = D->Front;
        D->Front->Next = NULL;
    }
    else // 多个结点的一般情况
    {
        D->Front->Next = tmp->Next;
        tmp->Next->Last = D->Front;
    }
    ret = tmp->Element;
    free(tmp);
    
    return ret;
}


int Inject( ElementType X, Deque D )
{
    PtrToNode tmp = (PtrToNode)malloc(sizeof(struct Node));
    
    if (!tmp) // 结点申请失败
        return 0;
    tmp->Element = X;
    tmp->Next = NULL;
    tmp->Last = NULL;
    
    // 双端队列为空
    if (D->Front == D->Rear)
    {
        D->Front->Next = tmp;
        tmp->Last = D->Front;
        D->Rear = tmp;
    }
    else // 不为空的一般情况
    {
        D->Rear->Next = tmp;
        tmp->Last = D->Rear;
        D->Rear = tmp;
    }
    return 1;
}

ElementType Eject( Deque D )
{
    ElementType ret;
    PtrToNode tmp;
    
    // 队列为空
    if (D->Front == D->Rear)
        return ERROR;
    
    tmp = D->Rear;
    
    // 只有一个结点
    if (D->Front->Next == D->Rear)
    {
        D->Rear = D->Front;
        D->Front->Next = NULL;
    }
    else // 多个结点的一般情况
    {
        D->Rear = tmp->Last;
        D->Rear->Next = NULL;
    }
    ret = tmp->Element;
    free(tmp);
    
    return ret;
}