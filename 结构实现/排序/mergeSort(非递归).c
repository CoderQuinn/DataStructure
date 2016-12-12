ypedef int ElementType;

void Merge( ElementType A[], ElementType TmpA[],
           int left, int right, int rightEnd )
{
    int leftEnd, tmpL;
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
}

void MergePass( ElementType A[], ElementType TmpA[], int N, int length )
{
    int i, j;
    for (i = 0; i <= N- 2*length; i += 2*length)
        Merge(A, TmpA, i, i+length, i+2*length-1);
    if (i + length < N)
        Merge(A, TmpA, i, i+length, N-1);
    else
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
}

void Merge_sort( ElementType A[], int N )
{
    ElementType *TmpA;
    int length;
    length = 1;
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL)
    {
        while (length < N)
        {
            MergePass(A, TmpA, N, length);
            length *= 2;
            MergePass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else
        printf(" 空间不足 ");
}
