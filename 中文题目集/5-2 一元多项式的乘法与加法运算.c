#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef; // 系数
    int expon; // 指数
    Polynomial link; // 指向下一个结点
};

// 将新结点插入到链表的尾部,参数为值传递，帮rear为指针的指针，才能修改尾部的指针
void Attach(int c, int e, Polynomial *rear)
{
    Polynomial p;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->coef = c;
    p->expon = e;
    p->link = NULL;
    (*rear)->link = p;
    *rear = p;
}

Polynomial ReadPoly()
{
    int c, e, N;
    Polynomial p, t, rear;
    
    // 增加一临时头结点，方便操作
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->link = NULL;
    rear = p;

    scanf("%d", &N);
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &rear);
    }
    
    // 删除临时头结点
    t = p;
    p = p->link;
    free(t);
    return p;
}

Polynomial Mult(Polynomial p1, Polynomial p2)
{
    Polynomial p, t, rear;
    Polynomial t1, t2;
    int c, e;
    
    if (!p1 || !p2)
        return NULL;
    
    // 增加一临时头结点，方便操作
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->link = NULL;
    rear = p;
    
    t1 = p1;
    t2 = p2;
    while (t2)
    {
        Attach(t1->coef*t2->coef, t1->expon+t2->expon, &rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    
    while (t1)
    {
        t2 = p2;
        rear = p;
        while (t2)
        {
            c = t1->coef*t2->coef;
            e = t1->expon+t2->expon;
            while (rear->link && rear->link->expon > e)
                rear = rear->link;
            if (rear->link && rear->link->expon == e)
            {
                if (c + rear->link->coef != 0)
                    rear->link->coef += c;
                else
                {
                    t = rear->link;
                    rear->link = t->link;
                    free(t);
                }
            }
            else
            {
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = NULL;
                t->link = rear->link;
                rear->link = t;
                rear = rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    
    
    // 删除临时头结点
    t = p;
    p = p->link;
    free(t);
    return p;
    
}

Polynomial Add(Polynomial p1, Polynomial p2)
{
    Polynomial p, t, rear;
    
    // 增加一临时头结点，方便操作
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->link = NULL;
    rear = p;
    
    while (p1 && p2)
    {
        if (p1->expon > p2->expon)
        {
            Attach(p1->coef, p1->expon, &rear);
            p1 = p1->link;
        }
        else if(p1->expon < p2->expon)
        {
            Attach(p2->coef, p2->expon, &rear);
            p2 = p2->link;
        }
        else
        {
            if (p1->coef + p2->coef != 0)
                Attach(p1->coef + p2->coef, p1->expon, &rear);
            p1 = p1->link;
            p2 = p2->link;
        }
    }
    
    while (p1)
    {
        Attach(p1->coef, p1->expon, &rear);
        p1 = p1->link;
    }
    
    while (p2)
    {
        Attach(p2->coef, p2->expon, &rear);
        p2 = p2->link;
    }
    
    // 删除临时头结点
    t = p;
    p = p->link;
    free(t);
    return p;
}

void PrintPoly(Polynomial p)
{
    int flag;
    if (p == NULL)
    {
        printf("0 0\n");
        return;
    }
    
    flag = 0;
    while (p)
    {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", p->coef, p->expon);
        p = p->link;
    }
    printf("\n");
}

int main()
{
    Polynomial p1, p2, pM, pA;
    p1 = ReadPoly();
    p2 = ReadPoly();
    
//    PrintPoly(p1);
//    PrintPoly(p2);

    pM = Mult(p1, p2);
    PrintPoly(pM);
    
    pA = Add(p1, p2);
    PrintPoly(pA);
    
    return 0;
}