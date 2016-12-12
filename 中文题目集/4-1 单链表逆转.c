#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Reverse(List L)
{
    PtrToNode pre, cur, tmp, newL;
    pre = NULL;
    cur = L;
    while (cur != NULL)
    {
        tmp = cur->Next;
        if (tmp == NULL)
            newL = cur;
        cur->Next = pre;
        pre = cur;
        cur = tmp;
    }
    return newL;
}