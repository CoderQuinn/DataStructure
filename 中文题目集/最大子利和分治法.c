#include <stdio.h>

int MaxIn3(int a, int b, int c)
{
    return a > b ? ( a > c ? a : c ) : ( b > c ? b : c );
}

int DivideAndConquer(int a[], int left, int right)
{
    // 左右子问题的解
    int maxLeftSum, maxRightSum;
    int thisLeftBorderSum, thisRightBorderSum;
    int maxLeftBorderSum, maxRightBorderSum;
    int center, i;
    
    // 递归出口，子列只有一个数字
    if (left == right)
    {
        if (a[left] > 0)
            return a[left];
        else
            return 0;
    }
    
    // 下面是分的过程
    center = (left+right)/2;
    maxLeftSum = DivideAndConquer(a, left, center);
    maxRightSum = DivideAndConquer(a, center+1, right);
    
    // 求跨界的最大子列和
    
    thisLeftBorderSum = 0, maxLeftBorderSum = 0;
    // 从中线向左扫描
    for (i = center; i >= left; i--)
    {
        thisLeftBorderSum += a[i];
        if (thisLeftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = thisLeftBorderSum;
    }
    
    thisRightBorderSum = 0, maxRightBorderSum = 0;
    // 从中线向右扫描
    for (i = center+1; i <= right; i++)
    {
        thisRightBorderSum += a[i];
        if (thisRightBorderSum > maxRightBorderSum)
            maxRightBorderSum = thisRightBorderSum;
    }
    
    //  下面是治的结果
    return MaxIn3( maxLeftSum, maxRightSum, maxLeftBorderSum+maxRightBorderSum);
}

int MaxSubseqSum(int a[], int n)
{
    return DivideAndConquer(a, 0, n-1);
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