#include <stdio.h>
#include <stdlib.h>
#define Error -1
typedef int ElementType;

// defination of stack
typedef struct StackNode
{
    ElementType *data;
    int maxSize;
    int top;
} *Stack;

Stack s1, s2;
Stack StackCreate(int N)
{
    Stack s;
    s = (Stack)malloc( sizeof(struct StackNode) );
    s->data = (ElementType*)malloc(sizeof(ElementType)*N);
    s->maxSize = N;
    s->top = -1;
    return s;
}

int IsFull(Stack s)
{
    if (s->top == s->maxSize-1)
        return 1;
    else
        return 0;
}

int IsEmpty (Stack s )
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

void Push(Stack s, ElementType x)
{
    if (IsFull(s))
        return;
    else
        s->data[++(s->top)] = x;
}

ElementType Pop(Stack s)
{
    if (IsEmpty(s))
        return Error;
    else
        return s->data[(s->top)--];
}

int IsDigit(char x)
{
    if (x >= '0' && x <= '9')
        return 1;
    else
        return 0;
}

// defination of Queue
typedef struct QNOde
{
    Stack s1;
    Stack s2;
} *Queue;

void Swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

Queue Create(int n1, int n2)
{
    // 假设n1 <= n2
    Queue q;
    q = (Queue)malloc(sizeof(struct QNOde));
    
    if (n1 > n2)
        Swap(&n1, &n2);
    q->s1 = StackCreate(n1);
    q->s2 = StackCreate(n2);
    return q;
}

void AddQ(Queue q, ElementType item)
{
    if (IsFull(q->s1))
    {
        if (!IsEmpty(q->s2))
            printf("ERROR:Full\n");
        else
        {
            while (!IsEmpty(q->s1))
                Push(q->s2, Pop(q->s1));
            Push(q->s1, item);
        }
    }
    else
        Push(q->s1, item);
}

void DeleteQ(Queue q)
{
    if (!IsEmpty(q->s2))
        printf("%d\n", Pop(q->s2));
    else
    {
        if (IsEmpty(q->s1))
            printf("ERROR:Empty\n");
        else
        {
            while (!IsEmpty(q->s1))
                Push(q->s2, Pop(q->s1));
            printf("%d\n", Pop(q->s2));
        }
    }
}

int main()
{
    int c, N1, N2, a;
    Queue q;

    scanf("%d %d", &N1, &N2);
    q = Create(N1, N2);
    
    while ( (c = getchar()) != 'T')
    {
        switch (c)
        {
            case 'A':
                scanf(" %d", &a);; // 取到当前数字
                AddQ(q, a);
                break;
            case 'D':
                DeleteQ(q);
                break;
            default: // 过滤空格和其他无关字符
                break;
        }
    }
    return 0;
}