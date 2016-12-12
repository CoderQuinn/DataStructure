#include <stdio.h>
#define MAX 100000

int Min(int a, int b)
{
    return a < b ? a : b;
}

// 假设m<=n
int FindKth(int A[], int m, int B[], int n, int k)
{
    int indexOfA, indexOfB;
    if (m > n)
        return FindKth(B, n, A, m, k);
    if (m == 0)
        return B[k-1];
    if (k == 1)
        return Min(A[0], B[0]);
    
    indexOfA = Min(k/2, m);
    indexOfB = k-indexOfA;
    
    if (A[indexOfA-1] < B[indexOfB-1])
        return FindKth(A+indexOfA, m-indexOfA, B, n, k-indexOfA);
    else if(A[indexOfA-1] > B[indexOfB-1])
        return FindKth(A, m, B+indexOfB, n-indexOfB, k-indexOfB);
    else
        return A[indexOfA-1];
}

int FindMedian(int A[], int B[], int n)
{
    return FindKth(A, n, B, n, n);
}

int main()
{
    int i, N;
    int A[MAX], B[MAX];
    scanf("%d", &N);
    
    for (i = 0; i < N; i++)
        scanf(" %d", &A[i]);
    for (i = 0; i < N; i++)
        scanf(" %d", &B[i]);
    printf("%d", FindMedian(A, B, N));
    return 0;
}