#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define ERROR -1
typedef enum {false, true} bool;
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List MakeEmpty()
{
    List l;
    l = (List)malloc(sizeof(struct LNode));
    l->Last = -1;
    return l;
}

Position Find( List L, ElementType X )
{
    int i = 0;
    while (i <= L->Last && L->Data[i] != X)
        i++;
    if (i > L->Last)
        return ERROR;
    else
        return i;
}

bool Insert( List L, ElementType X, Position P )
{
    int i;
    if (L->Last == MAXSIZE-1)
    {
        printf("FULL");
        return false;
    }
    if (P < 0 || P > L->Last+1)
    {
        printf("ILLEGAL POSITION");
        return false;
    }
    for (i = L->Last; i >= P; i--)
        L->Data[i+1] = L->Data[i];
    L->Data[P] = X;
    L->Last++;
    return true;
}

bool Delete( List L, Position P )
{
    int i;
    if (P < 0 || P > L->Last)
    {
        printf("POSITION %d EMPTY", P);
        return false;
    }
    for (i = P; i < L->Last; i++)
        L->Data[i] = L->Data[i+1];
    L->Last--;
    return true;
}
