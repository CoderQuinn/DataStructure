#define Cutoff 50
typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType t;
    t = *a;
    *a = *b;
    *b = t;
}

void Insertion_Sort(ElementType A[], int N)
{
    int i, P;
    ElementType tmp;
    for (P = 1; P < N; P++)
    {
        tmp = A[P];
        for (i = P; i > 0 && A[i-1] > tmp; i--)
            A[i] = A[i-1];
        A[i] = tmp;
    }
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
    
    if (Cutoff <= right-left+1)
    {
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
    else
        Insertion_Sort(A+left, right-left+1);
    
}

void Quick_Sort(ElementType A[], int N)
{
    QuickSort(A, 0, N-1);
}