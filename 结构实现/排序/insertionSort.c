typedef int ElementType;

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