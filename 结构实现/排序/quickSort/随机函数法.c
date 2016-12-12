#define MAX 100000
typedef int ElementType;

int Rand(int N)
{
    srand(time(0));
    int num;
    num = rand()%N;
    //    printf("随机数: %d \n", num);
    return num;
}

void Swap(ElementType *a, ElementType *b)
{
    ElementType t;
    t = *a;
    *a = *b;
    *b = t;
}

ElementType Median3( ElementType A[], int left, int right )
{
    ElementType center;
    center = (left+right)/2;
    if (A[left] > A[center])
        Swap(&A[left], &A[center]);
    if (A[left] > A[right])
        Swap(&A[left], &A[right]);
    if (A[center] > A[right])
        Swap(&A[center], &A[right]);
    Swap(&A[center], &A[right-1]);
    return A[right-1];
}

void QuickSort(ElementType A[], int left, int right)
{
    int low, high, rand;
    ElementType pivot;
    
    if (left >= right)
        return; // 递归出口
    
    low = left-1;
    high = right;
    rand = Rand(right-left+1);
    pivot = A[left+rand];
    Swap(&A[left+rand], &A[right]);
    while (1)
    {
        while (low < high && A[++low] < pivot);
        while (low < high && A[--high] > pivot);
        if (low < high)
            Swap(&A[low], &A[high]);
        else
            break;
    }
    Swap(&A[low], &A[right]);
    QuickSort(A, left, low-1);
    QuickSort(A, low+1, right);
}

void Quick_Sort(ElementType A[], int N)
{
    QuickSort(A, 0, N-1);
}
