#include <stdio.h>
#include <stdlib.h>
#define ElementType char
/**
 *  abc--de-g--f---
 *  先序：abcdefg
 *  中序：cbegdfa
 *  后序: cgefdba
 */

typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinTree;
/**
 *  树结点的定义
 */
struct TreeNode
{
    ElementType data; // 结点数据
    BinTree left; // 指向左子树
    BinTree right; // 指向右子树
};

/**
 *  先序次序输入二叉树的结点的值，’-‘字符表示空树，创建一个二叉树
 */
BinTree binTreeCreate()
{
    BinTree t;
    char temp;
    scanf("%c", &temp);

    if ('-' == temp)
        t = NULL;
    else
    {
        t = (BinTree)malloc(sizeof(struct TreeNode));
        t->data = temp;
        t->left = binTreeCreate(t->left);
        t->right = binTreeCreate(t->right);
    }
    return t;
}

void binTreePreOrderTraversal(BinTree T)
{
    if(T)
    {
        printf("%c ", T->data);
        binTreePreOrderTraversal(T->left);
        binTreePreOrderTraversal(T->right);
    }
}

void binTreeInOrderTraversal(BinTree T)
{
    if(T)
    {
        binTreeInOrderTraversal(T->left);
        printf("%c ", T->data);
        binTreeInOrderTraversal(T->right);
    }
}

void binTreePostOrderTraversal(BinTree T)
{
    if(T)
    {
        binTreePostOrderTraversal(T->left);
        binTreePostOrderTraversal(T->right);
        printf("%c ", T->data);
    }
}


int main()
{
    BinTree t = binTreeCreate();
    
    binTreePreOrderTraversal(t);
    printf("\n");
    
    binTreeInOrderTraversal(t);
    printf("\n");
    
    binTreePostOrderTraversal(t);
    printf("\n");
    return 0;
}
