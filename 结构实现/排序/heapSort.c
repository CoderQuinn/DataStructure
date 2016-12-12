typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void PercolateDown(ElementType A[], int p, int N)
{
    int parent, child;
    ElementType x;
    
    x = A[p];
    parent = p;
    while( parent*2+1 <= N-1 )
    {
        child = parent*2+1;
        if (child != N-1 && A[child+1] > A[child])
            child++;
        if (x >= A[child])
            break;
        else
            A[parent] = A[child];
        parent = child;
    }
    A[parent] = x;
}

void Heap_Sort(ElementType A[], int N)
{
    int i;
    for (i = N/2-1; i >= 0; i--) /* buildMaxHeap */
        PercolateDown(A, i, N);
    for (i = N-1; i > 0; i--)
    {
        Swap(&A[0], &A[i]); /* deleteMax */
        PercolateDown(A, 0, i);
    }
    
}