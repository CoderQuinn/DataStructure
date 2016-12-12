#include <stdio.h>
#define MAX 100000

// O(m+n)
int FindMedian(int A[], int B[], int n)
{
    int i, j, tmp, cnt;
    i = 0;
    j = 0;
    cnt = 0;
    while (cnt < n)
    {
        if (A[i] <= B[j])
            tmp = A[i++];
        else
            tmp = B[j++];
        cnt++;
    }
    return tmp;
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