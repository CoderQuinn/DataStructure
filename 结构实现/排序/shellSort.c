/*
原始的希尔排序序列：D = N/2; D > 0; D /= 2;
 
Sedgewick序列:
0, 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 67084289, 150958081, 268386305, 603906049, 1073643521
*/
typedef int ElementType;

void Shell_Sort(ElementType A[], int N)
{
    int Si, D, P;
    int i, tmp;
    int Sedgewick[] = {0, 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769};
    
    Si = 0;
    while (Sedgewick[Si] <= N)
        Si++;
    for (D = Sedgewick[--Si]; D > 0; D = Sedgewick[--Si])
    {
        for (P = D; P < N; P++)
        {
            tmp = A[P];
            for (i = P; i >= D && A[i-D] > tmp ; i -= D)
                A[i] = A[i-D];
            A[i] = tmp;
        }
    }
}