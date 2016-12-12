#include <stdio.h>
#define MAX 10
#define Null -1
typedef char ElementType;
typedef int Tree;

typedef struct Node TreeNode;
struct Node
{
    ElementType val;
    Tree left;
    Tree right;
};
TreeNode T1[MAX], T2[MAX];

Tree BuildTree(TreeNode t[])
{
    Tree root;
    int i, N;
    char cl, cr;
    int check[MAX];
    
    scanf("%d", &N);
    if (N <= 0)
        return Null;
    
    for (i = 0; i < N; i++)
        check[i] = 0;
    
    for (i = 0; i < N; i++)
    {
        scanf(" %c %c %c", &t[i].val, &cl, &cr);
        if (cl != '-')
        {
            t[i].left = cl - '0';
            check[t[i].left] = 1;
        }
        else
            t[i].left = -1;
        if (cr != '-')
        {
            t[i].right = cr - '0';
            check[t[i].right] = 1;
        }
        else
            t[i].right = -1;
    }
    for (i = 0; i < N; i++)
        if (!check[i])
        {
            root = i;
            break;
        }
    return root;
}

int Isomorphic(Tree r1, Tree r2)
{
    if (r1 == Null && r2 == Null)
        return 1;
    
    if ( (r1 == Null && r2 != Null) || (r1 != Null && r2 == Null) )
        return 0;
    
    if (T1[r1].val != T2[r2].val)
        return 0;
    
    if (T1[r1].left == Null && T2[r2].left == Null)
        return Isomorphic(T1[r1].right, T2[r2].right);
    
    if (T1[r1].left != Null && T2[r2].left != Null && T1[T1[r1].left].val == T2[T2[r2].left].val )
        return Isomorphic(T1[r1].left, T2[r2].left) && Isomorphic(T1[r1].right, T2[r2].right);
    else
        return Isomorphic(T1[r1].left, T2[r2].right) && Isomorphic(T1[r1].right, T2[r2].left);
}

int main()
{
    Tree r1, r2;
    r1 = BuildTree(T1);
    r2 = BuildTree(T2);
    
    if (Isomorphic(r1, r2))
        printf("Yes");
    else
        printf("No");
    return 0;
}