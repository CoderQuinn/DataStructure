#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

// 难点：数组模拟堆栈及字符和数字的处理
ElementType EvalPostfix( char *expr )
{
    int Top;
    int i, j;
    int flag, type;
    char num[Max_Expr];
    ElementType tmp, a, b, sign;
    ElementType Stack[Max_Expr];
    
    Top = -1;
    i = 0;
    flag = 0;
    sign = 1.0;
    
    while ( (type = expr[i]) != '\0' )
    {
        if (type == ' ');
        else if (type >= '0' && type<= '9')
        {
            j = 0;
            num[j] = type;
            while ( ( type=expr[i+1] ) != '\0' && type>='0' && type<='9')
            {
                num[++j] = expr[++i];
            }
            if (type == '.') // 如果是小数
            {
                num[++j] = expr[++i];
                while ( ( type=expr[i+1] ) != '\0' && type>='0' && type<='9')
                {
                    num[++j] = expr[++i];
                }
            }
            num[++j] = '\0';
            tmp = atof(num);
            Stack[++Top] = sign*tmp;
            sign = 1.0;
        }
        else if(type == '+')
        {
            // 正号表示正数的情况
            if (expr[i+1] >= '0' && expr[i+1] <= '9')
            {
                sign = -1.0;
            }
            else
            {
                if (Top < 1)
                {
                    flag = 1;
                    break;
                }
                b = Stack[Top--];
                a = Stack[Top--];
                Stack[++Top] = a+b;
            }
        }
        else if(type == '-')
        {
            // 负号表示负数的情况
            if (expr[i+1] >= '0' && expr[i+1] <= '9')
            {
                sign = -1.0;
            }
            else
            {
                if (Top < 1)  // 栈中必须有两个数
                {
                    flag = 1;
                    break;
                }
                b = Stack[Top--];
                a = Stack[Top--];
                Stack[++Top] = a-b;
            }

        }
        else if(type == '*')
        {
            if (Top < 1)  // 栈中必须有两个数
            {
                flag = 1;
                break;
            }
            b = Stack[Top--];
            a = Stack[Top--];
            Stack[++Top] = a*b;
        }
        else if(type == '/')
        {
            if (Top < 1) // 栈中必须有两个数
            {
                flag = 1;
                break;
            }
            b = Stack[Top--];
            a = Stack[Top--];
            if (b != 0.0)
            {
                Stack[++Top] = a/b;
            }
            else
                flag = 1;
        }
        if (flag)
            break;
        i++;
    }
    if (flag || Top != 0)
        tmp = Infinity;
    else
        tmp = Stack[Top--];
    return tmp;
}

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}
