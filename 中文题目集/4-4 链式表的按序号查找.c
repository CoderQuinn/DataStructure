 #include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

ElementType FindKth( List L, int K )
{
    int i;
    PtrToLNode p;
    
    i = 1;
    p = L;
    while (p && i < K)
    {
        p = p->Next;
        i++;
    }
    if (p && i == K)
        return p->Data;
    else
        return ERROR;
}
