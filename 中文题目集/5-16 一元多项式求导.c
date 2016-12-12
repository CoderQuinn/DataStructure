#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int c, int e, Polynomial *rear)
{
    Polynomial p;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->coef = c;
    p->expon = e;
    (*rear)->link = p;
    *rear = p;
}

Polynomial ReadPoly()
{
    int c, e;
    Polynomial p, rear, t;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->link = NULL;
    rear = p;
    
    while (scanf("%d %d", &c, &e) != EOF)
        Attach(c, e, &rear);
    t = p;
    p = p->link;
    free(t);
    return p;
}

Polynomial DifferentationPoly(Polynomial p)
{
    Polynomial cur, pre;
    cur = p;
    pre = NULL;
    while (cur && cur->expon)
    {
        cur->coef *= cur->expon;
        cur->expon--;
        pre = cur;
        cur = cur->link;
    }
    // 判断常数项的问题
    if (cur)
    {
        if (pre == NULL) // 只有常数项
            cur->coef = 0;
        else
        {
            // 常数项求导后为0
            free(cur);
            pre->link = NULL;
        }
    }
    return p;
}

void PrintPoly(Polynomial p)
{
    int flag = 0;
    Polynomial t= p;
    while (t)
    {
        if (flag)
            printf(" ");
        else
            flag = 1;
        printf("%d %d", t->coef, t->expon);
        t = t->link;
    }
}

int main()
{
    Polynomial p;
    p = ReadPoly();
    p = DifferentationPoly(p);
    PrintPoly(p);
    return 0;
}
