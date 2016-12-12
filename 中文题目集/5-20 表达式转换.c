#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 21
#define Number 0
typedef char ElementType;

typedef struct StackNode
{
    ElementType data[MAX];
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
    if (s->top == MAX-1)
        return;
    s->data[++(s->top)] = x;
}

int IsEmpty(Stack s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

ElementType Pop(Stack s)
{
    if (IsEmpty(s))
        return '\0';
    else
        return s->data[(s->top)--];
}

ElementType Top(Stack s)
{
    if (IsEmpty(s))
        return '\0';
    return s->data[(s->top)];
}

int Priority(char op)
{
    int p;
    // 返回操作数的优先级
    switch (op)
    {
        case '+':
        case '-':
            p = 1;
            break;
        case '/':
        case '*':
            p = 2;
            break;
        default:
            p = 0;
            break;
    }
    return p;
}

int main()
{
    int i, type, flag;
    char s[MAX];
    Stack t = CreateStack();
    
    scanf("%s", s);
    flag = i = 0;
    
    while ( (type = s[i]) != '\0' )
    {
        switch (type)
        {
            case '+':
                if ( i == 0 || ( i >0 && s[i-1] == '(') ) // 数字前面的正号表示正数的情况
                    break;
            case '-':
                if ( i == 0 || ( i >0 && s[i-1] == '(' ) ) // 数字前面的负号表示负数的情况
                {
                    if (!flag)
                        flag = 1;
                    else
                        printf(" ");
                    printf("-");
                    if (isdigit( type= s[++i] ))
                    {
                        printf("%c", type);
                        while ( isdigit(s[i+1]) || s[i+1] == '.' )
                            printf("%c", s[++i]);
                    }
                    break;
                }
            case '*':
            case '/':
                while (Priority(type) <= Priority(Top(t)))
                    printf(" %c", Pop(t));
                if ( Priority(type) > Priority(Top(t)) )
                    Push(t, type);
                break;
            case '(':
                Push(t, '(');
                break;
            case ')':
                while ( Top(t) != '(' )
                    printf(" %c", Pop(t));
                Pop(t); // 弹出'{'
                break;
            default: // 数字前面没有+-号的一般情况
                if (!flag)
                    flag = 1;
                else
                    printf(" ");
                if (isdigit(type)) // 一直输出直到碰到操作符
                {
                    printf("%c", type);
                    while ( isdigit(s[i+1]) || s[i+1] == '.' )
                        printf("%c", s[++i]);
                }
                break;
        }
        i++;
    }
    while(!IsEmpty(t))
        printf(" %c", Pop(t));
    return 0;
}