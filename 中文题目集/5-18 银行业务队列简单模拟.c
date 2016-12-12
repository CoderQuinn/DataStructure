#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1001
#define ERROR -1
typedef int ElementType;

typedef struct QNode
{
    ElementType data[MAXSIZE];
    int front;
    int rear;
} *Queue;

Queue CreateQueue()
{
    Queue q;
    q = (Queue)malloc(sizeof(struct QNode));
    q->front = 0;
    q->rear = 0;
    return q;
}

int IsFull(Queue q)
{
    if ( (q->rear+1) % MAXSIZE == q->front )
        return 1;
    else
        return 0;
}

int IsEmpty(Queue q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

void AddQ(Queue q, ElementType x)
{
    if (IsFull(q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear+1)%MAXSIZE;
        q->data[q->rear] = x;
    }
}

ElementType DeleteQ(Queue q)
{
    if (IsEmpty(q))
    {
        printf("Queue is empty\n");
        return ERROR;
    }
    else
    {
        q->front = (q->front+1)%MAXSIZE;
        return q->data[q->front];
    }
}

int main()
{
    int N, cur, i, flag;
    Queue q1, q2;
    flag = 0;
    q1 = CreateQueue();
    q2 = CreateQueue();
    
    scanf("%d", &N);
    // read information
    for (i = 0; i < N; i++)
    {
        scanf(" %d", &cur);
        if (cur % 2) // 奇数
            AddQ(q1, cur);
        else
            AddQ(q2, cur);
    }
    
    // output
    while (!IsEmpty(q1) && !IsEmpty(q2))
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf( "%d", DeleteQ(q1) );
        if (!IsEmpty(q1))
            printf( " %d", DeleteQ(q1) );
        printf( " %d", DeleteQ(q2) );
    }
    
    while (!IsEmpty(q1))
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf( "%d", DeleteQ(q1) );
    }
    
    while (!IsEmpty(q2))
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf( "%d", DeleteQ(q2) );
    }
    
    return 0;
}