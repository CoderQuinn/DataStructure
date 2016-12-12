#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

List Read(); /* 细节在此不表 */

int Length( List L )
{
    int i = 0;
    List p = L;
    while (p != NULL)
    {
        p = p->Next;
        i++;
    }
    return i;
}