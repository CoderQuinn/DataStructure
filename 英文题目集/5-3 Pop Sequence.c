#include <stdio.h>
#include <stdlib.h>
#define Error -1

typedef int ElementType;

typedef struct StackNode
{
    ElementType *data;
    int maxSize;
    int top;
} *Stack;

Stack Create(int N)
{
    Stack s;
    s = (Stack)malloc(sizeof(struct StackNode));
    s->data = (ElementType *)malloc(sizeof(ElementType) * N);
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

int IsEmpty(Stack s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

int Push(Stack s, ElementType x)
{
    if (IsFull(s))
        return 0;
    else
    {
        s->data[++(s->top)] = x;
        return 1;
    }
}

int Pop(Stack s)
{
    if (IsEmpty(s))
        return Error;
    else
        return s->data[(s->top)--];
}

int Top(Stack s)
{
    if (IsEmpty(s))
        return Error;
    else
        return s->data[s->top];
}

int IsPopSeq(int In[], int maxSize, int n)
{
    int i, j;
    Stack s;
    
    j = 0;
    s = Create(maxSize);
    for (i = 1; i <= n; i++)
    {
        if (!Push(s, i))
            return 0;
        while (Top(s) == In[j])
        {
            Pop(s);
            j++;
        }
    }
    if (j == n)
        return 1;
    else
        return 0;
    
}

int main()
{
    int i, j, M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    
    int In[N];
    
    for (i = 0; i < K; i++)
    {
        for (j = 0; j < N; j++)
            scanf("%d", &In[j]);
        if (IsPopSeq(In, M, N))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}