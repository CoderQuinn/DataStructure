#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef enum {false, true} bool;
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

List MakeEmpty()
{
    List l;
    l = (PtrToLNode)malloc(sizeof(struct LNode));
    l->Next = NULL;
    return l;
}

Position Find( List L, ElementType X )
{
    PtrToLNode p;
    p = L->Next;
    while (p != NULL && p->Data != X)
        p = p->Next;
    if (p != NULL)
        return p;
    else
        return ERROR;
}

bool Insert( List L, ElementType X, Position P )
{
    PtrToLNode pre, t;
    pre = L;
    
    while (pre && pre->Next != P)
        pre = pre->Next;
    if (pre == NULL) // P插入位置不合法
    {
        printf("Wrong Position for Insertion\n");
        return false;
    }
    else
    {
        t = (PtrToLNode)malloc(sizeof(struct LNode));
        t->Data = X;
        t->Next = pre->Next;
        pre->Next = t;
        return true;
    }
}

bool Delete( List L, Position P )
{
    PtrToLNode pre, t;
    pre = L;
    
    while (pre && pre->Next != P)
        pre = pre->Next;
    if (pre == NULL) // P位置不合法
    {
        printf("Wrong Position for Deletion\n");
        return false;
    }
    else
    {
        t = pre->Next;
        pre->Next = t->Next;
        free(t);
        return true;
    }
}

int main()
{
    List L;
    ElementType X;
    Position P;
    int N;
    bool flag;
    
    L = MakeEmpty();
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        flag = Insert(L, X, L->Next);
        if ( flag==false ) printf("Wrong Answer\n");
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        P = Find(L, X);
        if ( P == ERROR )
            printf("Finding Error: %d is not in.\n", X);
        else {
            flag = Delete(L, P);
            printf("%d is found and deleted.\n", X);
            if ( flag==false )
                printf("Wrong Answer.\n");
        }
    }
    flag = Insert(L, X, NULL);
    if ( flag==false )
        printf("Wrong Answer\n");
    else
        printf("%d is inserted as the last element.\n", X);
    P = (Position)malloc(sizeof(struct LNode));
    flag = Insert(L, X, P);
    if ( flag==true )
        printf("Wrong Answer\n");
    flag = Delete(L, P);
    if ( flag==true )
        printf("Wrong Answer\n");
    for ( P=L->Next; P; P = P->Next )
        printf("%d ", P->Data);
    return 0;
}