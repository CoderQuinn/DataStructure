#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;

struct AVLNode
{
    ElementType data; // 结点数据
    AVLTree left; // 指向右子树
    AVLTree right; // 指向左子树
    int height; // 树高
};

int Max(int a, int b)
{
    return a > b ? a : b;
}

static int GetHeight(AVLTree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}
// LL旋转（左单旋）
/* 注意：A必须有一个左子结点B */
/* 将A与B做左单旋,更新A与B的高度,返回新的根结点B */
AVLTree SingleLeftRotation(AVLTree a)
{
    AVLTree b = a->left;
    a->left = b->right;
    b->right = a;
    a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;
    b->height = Max(GetHeight(b->left), a->height) + 1;
    return b; /* new root */
}

// RR旋转（右单旋）
/* 注意：A必须有一个右子结点B */
/* 将A与B做右单旋,更新A与B的高度,返回新的根结点B */
AVLTree SingleRightRotation(AVLTree a)
{
    AVLTree b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;
    b->height = Max(a->height, GetHeight(b->right))+1;
    return b;
}

// LR旋转
/* 注意：A必须有一个左子结点B,且B必须有一个右子结点C */
AVLTree DoubleLeftRightRotation(AVLTree a)
{
    a->left = SingleRightRotation(a->left); /* 将B与C做右单旋,C被返回 */
    /* 将A与C做左单旋,C被返回*/
    return SingleLeftRotation(a);
}

// RL旋转
/* 注意：A必须有一个右子结点B,且B必须有一个左子结点C */
AVLTree DoubleRightLeftRotation(AVLTree a)
{
    a->right = SingleLeftRotation(a->right); /* 将B与C做左单旋，C被返回 */ /* 将A与C做右单旋,C被返回*/
    return SingleRightRotation(a);
}

AVLTree NewNode(ElementType x)
{
    AVLTree t = (AVLTree)malloc(sizeof(struct AVLNode));
    t->data = x;
    t->height = 0;
    t->left = t->right = NULL;
    return t;
}
AVLTree Insert(AVLTree t, ElementType x)
{
    if (t == NULL) // 若插入空树,则新建包含一个结点的树
        t = NewNode(x);
    else if(x < t->data)
    { // 插入t的左子树
        t->left = Insert(t->left, x);
        // 如果需要左旋
        if (GetHeight(t->left) - GetHeight(t->right) == 2)
        {
            if (x < t->left->data)
                t = SingleLeftRotation(t); // LL旋转
            else
                t = DoubleLeftRightRotation(t); // LR旋转
        }
    }
    else if(x > t->data)
    { // 插入t的右子树
        t->right = Insert(t->right, x);
        if (GetHeight(t->right) - GetHeight(t->left) == 2)
        {
            if (x > t->right->data)
                t = SingleRightRotation(t); // RR旋转
            else
                t = DoubleRightLeftRotation(t); // RL旋转
        }
    }
    t->height = Max(GetHeight(t->left), GetHeight(t->right))+1;
    return t;
}

AVLTree MakeTree(int N)
{
    int i, x;
    AVLTree t;
    scanf("%d", &x);
    t = NewNode(x);
    for (i = 1; i < N; i++)
    {
        scanf("%d", &x);
        t = Insert(t, x);
    }
    return t;
}
int main()
{
    int N;
    AVLTree t;
    scanf("%d", &N);
    t = MakeTree(N);
    printf("%d", t->data);
    return 0;
}