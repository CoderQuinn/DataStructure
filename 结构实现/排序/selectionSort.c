typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Selection_Sort(ElementType A[], int N)
{
    int i, P, minP;
    for (P = 0; P < N-1; P++)
    {
        minP = P;
        for (i = P+1; i < N; i++)
            if (A[i] < A[minP])
                minP = i;
        if (minP != P)
            Swap(&A[minP], &A[P]);
    }
}