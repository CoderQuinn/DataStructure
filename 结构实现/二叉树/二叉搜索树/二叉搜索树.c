#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct TreeNode *Position;
typedef Position BinTree;

struct TreeNode
{
    int valve;
    Position left;
    Position right;
};

int main()
{
    Position Find( ElementType X, BinTree BST );
    Position FindMin( BinTree BST );
    Position FindMax( BinTree BST );
    BinTree Insert( ElementType X, BinTree BST );
    BinTree Delete( ElementType X, BinTree BST );
    return 0;
}
//// 递归实现
//Position FindMin(BinTree BST)
//{
//    if (BST == NULL)
//        return NULL;
//    else if(BST->left == NULL)
//        return BST;
//    else
//        return FindMin(BST->left);
//}
//
//Position FindMax(BinTree BST)
//{
//    if (BST == NULL)
//        return NULL;
//    else if(BST->right == NULL)
//        return BST;
//    else
//        return FindMax(BST->right);
//}
//
//Position Find(ElementType x, BinTree BST)
//{
//    if (BST == NULL)
//        return NULL;
//    if (x > BST->valve)
//        return Find(x, BST->right); // 在左子树中递归查找
//    else if(x < BST->valve)
//        return Find(x, BST->left); // 在右子树中递归查找
//    else
//        return BST; // 查找成功，返回结点地址
//}

// 非递归实现
Position FindMin(BinTree BST)
{
    if (BST) {
        while (BST->left)
        {
            BST = BST->left;
        }
    }
    return BST;
}

Position FindMax(BinTree BST)
{
    if (BST) {
        while (BST->right)
        {
            BST = BST->right;
        }
    }
    return BST;
}

Position Find(ElementType x, BinTree BST)
{
    while (BST)
    {
        if (x < BST->valve)
            BST = BST->left;
        else if(x > BST->valve)
            BST = BST->right;
        else
            return BST;
    }
    return NULL;
}

// 递归插入
BinTree Insert(ElementType x, BinTree BST)
{
    if (BST == NULL) // 若原树为空，生成并返回一个结点的二叉搜索树
    {
        BST = malloc(sizeof(struct TreeNode));
        BST->valve = x;
        BST->left = BST->right = NULL;
    }
    else // 开始找要插入元素的位置
    {
        if (x < BST->valve) // 递归插入左子树
            BST->left = Insert(x, BST->left);
        else if(x > BST->valve) // 递归插入右子树
            BST->right = Insert(x, BST->right);
    }
    return BST;
}

// 递归删除
BinTree Delete(ElementType x,BinTree BST)
{
    Position tmp;
    
    if (BST == NULL);
    else
    {
        if (x < BST->valve) // 从左子树递归删除
            BST->left = Delete(x, BST->left);
        else if(x > BST->valve) // 从右子树递归删除
            BST->right = Delete(x, BST->right);
        else // BST就是要删除的这个结点
        {
            // 如果被删除结点有左右两个子结点
            if (BST->left && BST->right)
            {
                // 从右子树中找到最小的元素填充删除结点
                tmp = FindMin(BST->right);
                BST->valve = tmp->valve;
                // 从右子树中删除最小的结点
                BST->right = Delete(BST->valve, BST->right);
            }
            else // 被删除结点有一个或无子结点
            {
                tmp = BST;
                if (BST->left == NULL) // 只有右孩子或无子结点
                    BST = BST->right;
                else // 只有左孩子或无子结点
                    BST = BST->left;
                free(tmp);
            }
        }
    }
    return BST;
}
