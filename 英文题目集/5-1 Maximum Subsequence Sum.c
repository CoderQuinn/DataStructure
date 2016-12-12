#include <stdio.h>

int MaxSubSum(int A[], int N, int *L, int *R)
{
    int i, j;
    int thisSum, maxSum;
    
    j = 0; // 记录最大子列的最左边项序号
    thisSum = maxSum = 0;
    for (i = 0; i < N; i++)
    {
        thisSum += A[i];
        if (thisSum > maxSum)
        {
            maxSum = thisSum;
            *L = A[j];
            *R = A[i];
        }
        else if(thisSum < 0)
        {
            thisSum = 0;
            j = i+1;
        }
    }
    
    // 特殊情况，输入的序列全为负数，或者负数和0
    if (maxSum == 0)
    {
        i = 0;
        while (i < N)
        {
            if (A[i] == 0) // 是否为全负数
                break;
            i++;
        }
        if (i == N) // 全为负数
        {
            *L = A[0];
            *R = A[N-1];
        }
        else
        {
            *L = 0;
            *R = 0;
        }
    }
    return maxSum;
}

int main()
{
    int i, K, sum, leftNum, rightNum;
    scanf("%d", &K);
    int A[K];
    for (i = 0; i < K; i++)
        scanf(" %d", &A[i]);
    sum = MaxSubSum(A, K, &leftNum, &rightNum);
    printf("%d %d %d\n", sum, leftNum, rightNum);
    return 0;
}