typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType t;
    t = *a;
    *a = *b;
    *b = t;
}

void QuickSort(ElementType A[], int left, int right)
{
    int low, high;
    ElementType pivot;
    if (left >= right)
        return; // 递归出口
    low = left-1;
    high = right;
    pivot = A[left];
    Swap(&A[left], &A[right]);
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