#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50

typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinTree;

struct TreeNode
{
    char data;
    PtrToNode left;
    PtrToNode right;
};

BinTree CreateTree(char *pre, char *in, int len)
{
    int i;
    BinTree t;
    if ( len <= 0 )
        return NULL;
    
    t = (BinTree)malloc( sizeof(struct TreeNode) );
    t->data = pre[0];
    
    // 在中序序列中找到根结点，递归的建树
    for (i = 0; i < len; i++)
        if (pre[0] == in[i])
            break;
    
    t->left = CreateTree(pre+1, in, i);
    t->right = CreateTree(pre+i+1, in+i+1, len-i-1);
    
    return t;
}

int HeightOfBinTree(BinTree t)
{
    int leftH, rightH, maxH;
    
    if (t)
    {
        leftH = HeightOfBinTree(t->left);
        rightH = HeightOfBinTree(t->right);
        maxH = leftH > rightH ? leftH : rightH;
        return maxH+1;
    }
    else
        return 0;
}

int main()
{
    int i, N;
    char Pre[MAXSIZE], In[MAXSIZE];
    BinTree t;
    
    scanf("%d", &N);
 
    scanf("%s\n%s", Pre, In);
    
    t = CreateTree(Pre, In, N);
    printf("%d", HeightOfBinTree(t));
    
    return 0;
}