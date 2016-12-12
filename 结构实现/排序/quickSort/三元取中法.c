typedef int ElementType;

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
    int low, high;
    ElementType pivot;
    
    if (left >= right)
        return; // 递归出口
    
    pivot = Median3(A, left, right);
    low = left;
    high = right-1;
    while (1)
    {
        while (low < high && A[++low] < pivot);
        while (low < high && A[--high] > pivot);
        if (low < high)
            Swap(&A[low], &A[high]);
        else
            break;
    }
    Swap(&A[low], &A[right-1]);
    QuickSort(A, left, low-1);
    QuickSort(A, low+1, right);
}

void Quick_Sort(ElementType A[], int N)
{
    QuickSort(A, 0, N-1);
}
