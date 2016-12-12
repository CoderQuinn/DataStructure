#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node
{
    int data;
    PtrToNode next;
};

typedef PtrToNode List;

List ReadAndSolve()
{
    int K, num, cnt;
    List l;
    PtrToNode p, t, rear;
    l = (List)malloc(sizeof(struct Node));
    l->next = NULL;
    rear = l;
    cnt = 0;
    p = NULL;
    
    scanf("%d", &K);
    if (K == 0)
        return p;
    scanf("%d", &num);
    while (num >= 0)
    {
        t = (List)malloc(sizeof(struct Node));
        t->data = num;
        t->next = NULL;
        rear->next = t;
        rear = t;
        cnt++;
        if (cnt == 1)
            p = rear;
        if (cnt > K)
            p = p->next;
        scanf("%d", &num);
    }
    t = l;
    l = l->next;
    free(t);
    if (K > cnt)
        return NULL;
    else
        return p;
}

int main()
{
    PtrToNode p;
    p = ReadAndSolve();
    if (p)
        printf("%d", p->data);
    else
        printf("NULL");
    return 0;
}