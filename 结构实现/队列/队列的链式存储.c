#include <stdio.h>
#include <stdlib.h>
#define ELEMENTTYPE int
#define YES 1
#define NO 0

typedef struct Node *PtrToNode;
// 队列中的结点
struct Node
{
    ELEMENTTYPE data;
    PtrToNode next;
};
typedef PtrToNode Position;

struct QNode
{
    Position front; // 队列的头指针
    Position rear; // 队列的尾指针
    int maxSize; // 队列的最大容量
};
typedef struct QNode *Queue;

Queue CreateQueue(int maxSize)
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->front = q->rear = NULL;
    q->maxSize = maxSize;
    return q;
}

int IsFull(Queue q)
{
    return ((q->rear-q->front) == q->maxSize-1);
}

int IsEmpty(Queue q)
{
    return (q->front == NULL);
}

int AddQ(Queue q, ELEMENTTYPE x)
{
    if (IsFull(q))
    {
        printf("队列已满");
        return NO;
    }
    Position tempCell;
    tempCell = (Position)malloc(sizeof(struct Node));
    tempCell->data = x;
    tempCell->next = NULL;
    
    if (IsEmpty(q))
    {
        q->front = tempCell;
        q->rear = tempCell;
    }
    else
    {
        q->rear->next = tempCell;
        q->rear = tempCell;
    }
    return YES;
}

ELEMENTTYPE DeleteQ(Queue q)
{
    Position frontCell;
    ELEMENTTYPE frontVal;
    
    if (IsEmpty(q))
    {
        printf("队列空");
        return NO;
    }
    else
    {
        frontCell = q->front;
        // 若队列只有一个元素
        if (q->front == q->rear)
            q->front = q->rear = NULL;
            // 删除后队列置空
        else
            q->front = q->front->next;
        frontVal = frontCell->data;
        
        free(frontCell); // 释放被删除结点空间
        
        return frontVal;
    }
}

int main()
{
    // 测试队列的创建
    Queue q = CreateQueue(10);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    
    AddQ(q,10);
//    printf("%p %p %d\n", q->front, q->rear, q->maxSize);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    
    // 测试队列是否满
    printf("%d\n", IsFull(q));
    

    printf("%p %p\n", q->front, q->rear);
    int a = DeleteQ(q);
    printf("出队元素为%d\n", a);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    
    for (int i = 0; i <10; i++)
        AddQ(q,i+1);
    
    // 测试队列是否满
    printf("%d\n", IsFull(q));
    
    for (int i=0; i<q->maxSize; i++)
        printf("%d\t", DeleteQ(q));
    return 0;
}