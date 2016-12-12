#include <stdio.h>
#include <stdlib.h>
#define Max 31
#define Number 0

double F;
int error = 0;

int IsDigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

int GetOp(char *in)
{
    int i, c, nextC;
    
    while ( (in[0] = c = getchar()) == ' ' );
    in[1] = '\0';
    
    if ( !IsDigit(c) && c != '.' && ( nextC =getchar() ) == ' ')
        return c;
    
    // 带正负号数的特殊情况
    F = 1.0;
    if (c == '+' && IsDigit(nextC))
    {
        in[0] = c = nextC;
    }
    else if(c == '-' && IsDigit(nextC))
    {
        F = -F;
        in[0] = c = nextC;
    }
    
    i = 0;
    if ( IsDigit(c) )
        while ( IsDigit( in[++i] = c = getchar() ) );
    
    if (c == '.')
        while ( IsDigit( in[++i] = c = getchar() ) );
    // 当前的i不为数字，必为空格，置为'\0'
    in[i] = '\0';
    return Number;
}

double Exp()
{
    double ret;
    int type, a, b;
    char In[Max];
    
    type = GetOp(In);
    switch (type)
    {
        case '+':
            ret = Exp()+Exp();
            break;
        case '-':
            ret = Exp()-Exp();
            break;
        case '*':
            ret = Exp()*1.0*Exp();
            break;
        case '/':
            a = Exp();
            b = Exp();
            if (b != 0)
                ret = a * 1.0 / b;
            else
                error = 1;
            break;
        case Number:
            ret = F*atof(In);
            break;
    }
    return ret;
}

int main()
{
    double ret;
    ret = Exp();
    if (error)
        printf("ERROR");
    else
        printf("%.1f", ret);
    return 0;
}