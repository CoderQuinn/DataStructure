#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef enum { No,Yes } Bool;

typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElementType *data; // 存储元素的数组
    Position rear; // 队列的尾指针
    Position front; // 队列的头指针
    int maxSize; // 队列的最大容量
};
typedef PtrToQNode Queue;

Queue CreateQueue(int maxSize)
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    q->front = q->rear = 0;
    q->maxSize = maxSize;
    return q;
}

Bool IsFull(Queue q)
{
    return ((q->rear+1)%q->maxSize == q->front);
}

Bool AddQ(Queue q, ElementType x)
{
    if (IsFull(q))
        return No;
    q->rear = (q->rear+1)%q->maxSize;
    q->data[q->rear] = x;
    return Yes;
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
        return No;
    }
    else
    {
        q->front = (q->front+1)%q->maxSize;
        return q->data[q->front];
    }
}

int main()
{
    // 测试队列的创建
    Queue q = CreateQueue(10);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    
    AddQ(q,10);
    printf("%d %d\n", q->front, q->rear);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    
    // 测试队列是否满
    printf("%d\n", IsFull(q));
    int a = DeleteQ(q);
    printf("出队元素为%d %d %d\n", a, q->front, q->rear);
    
    // 测试队列是否为空
    printf("%d\n", IsEmpty(q));
    a = DeleteQ(q);
    
    for (int i = 0; i <10; i++)
        AddQ(q,i+1);
    
    // 测试队列是否满
    printf("%d\n", IsFull(q));
    printf("%d %d\n", q->front, q->rear);
    return 0;
}