#include <stdio.h>
#include <stdlib.h>

typedef struct LNode *PtrToNode;
struct LNode
{
    int val;
    PtrToNode next;
};
typedef PtrToNode List;

void Attach(int val, PtrToNode *rear)
{
    PtrToNode t;
    t = (PtrToNode)malloc(sizeof(struct LNode));
    t->val = val;
    t->next = NULL;
    (*rear)->next = t;
    *rear = t;
}

List ListRead()
{
    int k;
    List l;
    PtrToNode t, rear;
    l = (PtrToNode)malloc(sizeof(struct LNode));
    l->next = NULL;
    rear = l;
    
    scanf("%d", &k);
    while (k != -1)
    {
        Attach(k, &rear);
        scanf("%d", &k);
    }
    t = l;
    l = l->next;
    free(t);
    return l;
}

List ListMerge(List l1, List l2)
{
    List l;
    PtrToNode t, rear;
    
    if (!l1 && !l2) // 两个皆空
        return NULL;
    if (l1 && !l2) // l2空
        return l1;
    if (!l1 && l2) // l1空
        return l2;
    
    l = (PtrToNode)malloc(sizeof(struct LNode));
    l->next = NULL;
    rear = l;
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            Attach(l1->val, &rear);
            l1 = l1->next;
        }
        else
        {
            Attach(l2->val, &rear);
            l2 = l2->next;
        }
    }
    
    while (l1)
    {
        Attach(l1->val, &rear);
        l1 = l1->next;
    }
    while (l2)
    {
        Attach(l2->val, &rear);
        l2 = l2->next;
    }
    t = l;
    l = l->next;
    free(t);
    return l;
}

void PrintList(List l)
{
    int flag = 0;
    if (!l)
        printf("NULL");
    while (l)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d", l->val);
        l = l->next;
    }
}

int main()
{
    List l1, l2, l3;
    l1 = ListRead();
    l2 = ListRead();
    l3 = ListMerge(l1, l2);
    PrintList(l3);
    return 0;
}