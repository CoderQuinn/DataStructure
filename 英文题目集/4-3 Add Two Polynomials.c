#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Add( Polynomial a, Polynomial b )
{
    Polynomial p, t, rear;
    p = (Polynomial)malloc(sizeof(struct Node));
    p->Next = NULL;
    rear = p;
    
    while (a && b)
    {
        if (a->Exponent > b->Exponent)
        {
            t = (Polynomial)malloc(sizeof(struct Node));
            t->Coefficient = a->Coefficient;
            t->Exponent = a->Exponent;
            t->Next = NULL;
            rear->Next = t;
            rear = t;
            a = a->Next;
        }
        else if (a->Exponent < b->Exponent)
        {
            t = (Polynomial)malloc(sizeof(struct Node));
            t->Coefficient = b->Coefficient;
            t->Exponent = b->Exponent;
            t->Next = NULL;
            rear->Next = t;
            rear = t;
            b = b->Next;
        }
        else
        {
            if (a->Coefficient + b->Coefficient) {
                t = (Polynomial)malloc(sizeof(struct Node));
                t->Coefficient = a->Coefficient + b->Coefficient;
                t->Exponent = b->Exponent;
                t->Next = NULL;
                rear->Next = t;
                rear = t;
            }
            a = a->Next;
            b = b->Next;
        }
    }
    
    while (a)
    {
        t = (Polynomial)malloc(sizeof(struct Node));
        t->Coefficient = a->Coefficient;
        t->Exponent = a->Exponent;
        t->Next = NULL;
        rear->Next = t;
        rear = t;
        a = a->Next;
    }
    
    while (b)
    {
        t = (Polynomial)malloc(sizeof(struct Node));
        t->Coefficient = b->Coefficient;
        t->Exponent = b->Exponent;
        t->Next = NULL;
        rear->Next = t;
        rear = t;
        b = b->Next;
    }
    return p;
}