#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100

typedef struct
{
    int n; // 盘数
    char a; // 起始柱
    char b; // 辅助柱
    char c; // 目标柱
} ElementType;

ElementType ERROR;

// 顺序结构的栈
typedef struct StackNode
{
    ElementType data[MaxSize];
    int top;
} *Stack;

Stack CreateStack()
{
    Stack s;
    s = (Stack)malloc(sizeof(struct StackNode));
    s->top = -1;
    return s;
}

void Push(Stack s, ElementType x)
{
    // 栈满
    if (s->top == MaxSize-1)
        return;
    s->data[++(s->top)] = x;
}

ElementType Pop(Stack s)
{
    if (s->top == -1)
        return ERROR;
    else
        return s->data[(s->top)--];
}

void Hanoi(int N)
{
    Stack s;
    ElementType P, tmp;
    s = CreateStack();
    
    // 初始的N规模的问题
    P.n = N;
    P.a = 'a';
    P.b = 'b';
    P.c = 'c';
    
    Push(s, P);
    while (s->top != -1)
    {
        P = Pop(s);
        // 出口
        if (1 == P.n)
            printf("%c -> %c\n", P.a, P.c);
        else
        {
            // 分解为三个子问题的角，并逆序放入栈中
            // (n-1, b, a, c)
            tmp.n = P.n - 1;
            tmp.a = P.b;
            tmp.b = P.a;
            tmp.c = P.c;
            Push(s, tmp);
            
            // (1, a, b, c)
            tmp.n = 1;
            tmp.a = P.a;
            tmp.b = P.b;
            tmp.c = P.c;
            Push(s, tmp);
            
            tmp.n = P.n - 1;
            tmp.a = P.a;
            tmp.b = P.c;
            tmp.c = P.b;
            Push(s, tmp);
        }
    }
    
}

int main()
{
    int N;
    scanf("%d", &N);
    
    ERROR.n = -1;
    
    Hanoi(N);
    return 0;
}