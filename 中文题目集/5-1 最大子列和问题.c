#include <stdio.h>

// 穷举法 n的三次方
int MaxSubseqSum1(int a[], int n)
{
    int thisSum, maxSum;
    int i, j, k;
    maxSum = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
        {
            thisSum = 0;
            for (k = i; k <= j; k++)
                thisSum += a[k];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    return maxSum;
}

// 相同的i，不同的j n的平方
int MaxSubseqSum2(int a[], int n)
{
    int thisSum, maxSum;
    int i, j;
    maxSum = 0;
    for (i = 0; i < n; i++)
    {
        thisSum = 0;
        for (j = i; j < n; j++)
        {
            thisSum += a[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

int MaxSubseqSum(int a[], int n)
{
    int thisSum, maxSum;
    int i;
    thisSum = maxSum = 0;
    for (i = 0; i < n; i++)
    {
        thisSum += a[i];
        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}

int main()
{
    int K, i;
    scanf("%d", &K);
    int A[K];
    for (i = 0; i < K; i++)
    {
        scanf("%d", &A[i]);
    }
    printf("%d\n", MaxSubseqSum(A, K));
    return 0;
}