#include <stdio.h>
#define MAXN 100000
typedef int ElementType;
// 仅针对连续的正数排序
// T[]为元素的指针下标数组
void TableSort(ElementType A[], int T[], int N)
{
    ElementType tmp;
    int i, curI, nextI;
    for (i = 0; i < N; i++)
    {
        tmp = A[i];
        nextI = i;
        if (i != T[i])
        {
            do
            {
                curI = nextI;
                A[curI] = A[T[curI]];
                nextI = T[curI];
                T[curI] = curI; // 标记已经交换
            } while(T[nextI] != i);
            // 把tmp交换环的的最后一个元素
            curI = nextI;
            A[curI] = tmp;
            T[curI] = curI;
        }
    }
}

int main()
{

    int i, N, ret;
    int T[MAXN];
    ElementType A[MAXN];
    
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
        T[A[i]] = i;
    }
    TableSort(A, T, N);
    for (i = 0; i < N; i++)
        printf("%d ", A[i]);
    return 0;
}