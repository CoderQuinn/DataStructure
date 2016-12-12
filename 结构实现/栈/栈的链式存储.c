#include <stdio.h>
#include <stdlib.h>
#define ELEMENTTYPE int
#define YES 1
#define NO -1

typedef struct StackNode *PtrToNode;
struct StackNode
{
    ELEMENTTYPE data;
    PtrToNode next;
};
typedef PtrToNode Stack;

 /* 构建一个堆栈的头结点，返回该结点指针 */
Stack CreateStack( )
{
    Stack s = (Stack)malloc(sizeof(struct StackNode));
    s->next = NULL;
    return s;
}

/* 判断堆栈S是否为空，若是返回YES；否则返回NO */
int IsEmpty (Stack s)
{
    return (s->next == NULL);
}

/* 将元素X压入堆栈S */
void Push(Stack s, ELEMENTTYPE x)
{
    PtrToNode tempCell = (Stack)malloc(sizeof(struct StackNode));
    tempCell->data = x;
    tempCell->next = s->next;
    s->next = tempCell;
    return;
}

/* 删除并返回堆栈S的栈顶元素 */
ELEMENTTYPE Pop(Stack s)
{
    PtrToNode topCell;
    ELEMENTTYPE topVal;
    if (IsEmpty(s))
        return NO;
    topCell = s->next;
    s->next = topCell->next;
    topVal = topCell->data;
    free(topCell);
    return topVal;
}

int main()
{
    Stack s = CreateStack();
    
    // 测试IsEmpty
    printf("%d\n", IsEmpty(s));
    
    // 测试Push
    for (int i = 0; i < 10; i++)
        Push(s, i+1);

    // 测试Pop
    while (!IsEmpty(s))
        printf("%d\t", Pop(s));
    
    // 测试IsEmpty
    printf("\n%d\n", IsEmpty(s));
    
    return 0;
}