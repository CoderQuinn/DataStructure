/*** 递归实现 ***/
typedef int ElementType;

void Merge( ElementType A[], ElementType TmpA[],
           int left, int right, int rightEnd )
{
    int i, leftEnd, tmpL;
    int numElements;
    
    leftEnd = right-1;
    tmpL = left;
    numElements = rightEnd - left + 1;
    while (left <= leftEnd && right <= rightEnd)
    {
        if (A[left] <= A[right])
            TmpA[tmpL++] = A[left++];
        else
            TmpA[tmpL++] = A[right++];
    }
    while (left <= leftEnd)
        TmpA[tmpL++] = A[left++];
    while (right <= rightEnd)
        TmpA[tmpL++] = A[right++];
    for (i = 0; i < numElements; i++, rightEnd--)
        A[rightEnd] = TmpA[rightEnd];
}

void MergeSort( ElementType A[], ElementType TmpA[], int left, int rightEnd )
{
    int center;
    
    if (left < rightEnd)
    {
        center = (left+rightEnd) / 2;
        MergeSort(A, TmpA, left, center);
        MergeSort(A, TmpA, center+1, rightEnd);
        Merge(A, TmpA, left, center+1, rightEnd);
    }
}

void Merge_sort( ElementType A[], int N )
{
    ElementType *TmpA;
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL)
    {
        MergeSort(A, TmpA, 0, N-1);
        free(TmpA);
    }
}

