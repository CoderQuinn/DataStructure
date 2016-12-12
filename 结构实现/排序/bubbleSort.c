typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
    ElementType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Bubble_Sort(ElementType A[], int N)
{
    int i, P;
    int flag;
    for (P = N-1; P > 0; P--)
    {
        flag = 1;
        for (i = 0; i < P; i++)
            if (A[i] > A[i+1])
            {
                Swap(&A[i], &A[i+1]);
                flag = 0;
            }
        if (flag)
            break;
    }
}