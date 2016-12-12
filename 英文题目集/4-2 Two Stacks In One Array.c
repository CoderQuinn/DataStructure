#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

// codes implementation
Stack CreateStack( int MaxElements )
{
    Stack s = (Stack)malloc(sizeof(struct StackRecord));
    s->Capacity = MaxElements;
    s->Array = (ElementType *)malloc(sizeof(ElementType) * MaxElements);
    s->Top1 = -1;
    s->Top2 = MaxElements;
    return s;
}

int IsEmpty( Stack S, int Stacknum )
{
    if (Stacknum == 1)
    {
        if (S->Top1 == -1)
            return 1;
        else
            return 0;
    }
    else if(Stacknum == 2)
    {
        if (S->Top2 == S->Capacity)
            return 1;
        else
            return 0;
    }
    
}
int IsFull( Stack S )
{
    if ( S->Top2 - S->Top1 == 1 )
        return 1;
    else
        return 0;
}

int Push( ElementType X, Stack S, int Stacknum )
{
    if( IsFull(S) )
        return 0;
    if (Stacknum == 1)
        S->Array[++(S->Top1)] = X;
    else
        S->Array[--(S->Top2)] = X;
    return 1;
}

ElementType Top_Pop( Stack S, int Stacknum )
{
    if (IsEmpty(S, Stacknum))
        return ERROR;
    if (Stacknum == 1)
        return S->Array[(S->Top1)--];
    else
        return S->Array[(S->Top2)++];
}