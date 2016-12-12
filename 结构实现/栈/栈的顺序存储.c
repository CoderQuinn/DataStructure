#include <stdio.h>
#include <stdlib.h>
#define Elementtype int
#define Null -1
typedef enum {NO, YES} BOOL;

// Definition of the stack
struct StackNode
{
    Elementtype *element; // array pointer
    int top; // top pointer of the stack
    int maxSize;
};
typedef struct StackNode *Stack;

// Create

Stack stackCreate(int maxSize)
{
    Stack s = (Stack)malloc(sizeof(struct StackNode));
    s->element = (Elementtype *)malloc(maxSize * sizeof(Elementtype));
    s->maxSize = maxSize;
    s->top = -1;
    return s;
}

BOOL isFull(Stack s)
{
    return (s->top == s->maxSize-1);
}

BOOL push(Stack s, Elementtype x)
{
    if (isFull(s))
        return NO;
    s->element[++(s->top)] = x;
    return YES;
}

BOOL isEmpty(Stack s)
{
    return (s->top == -1);
}

Elementtype pop(Stack s)
{
    if (isEmpty(s))
        return Null;
    return s->element[(s->top)--];
}

Elementtype top(Stack s)
{
    if (isEmpty(s))
        return Null;
    return s->element[s->top];
}

int main()
{
    Stack s = stackCreate(9);
    
    // 测试isEmpty
    printf("%d\n", isEmpty(s));
    
    // 测试push
    for (int i = 0; i < s->maxSize; i++)
        push(s, i+1);
    
    // 测试isFull
    printf("%d\n", isFull(s));
    
    // 测试pop
    while (!isEmpty(s))
        printf("%d ", pop(s));
    return 0;
}