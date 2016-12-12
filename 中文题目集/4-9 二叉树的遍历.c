#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void InorderTraversal( BinTree BT )
{
    if (BT)
    {
        InorderTraversal(BT->Left);
        printf(" %c", BT->Data);
        InorderTraversal(BT->Right);
    }
}

void PreorderTraversal( BinTree BT )
{
    if (BT)
    {
        printf(" %c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void PostorderTraversal( BinTree BT )
{
    if (BT)
    {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c", BT->Data);
    }
}

void LevelorderTraversal( BinTree BT )
{
    BinTree t;
    BinTree q[1000];
    int front, rear;
    front = rear = 0;
    
    if (!BT)
        return;
    
    // 根结点入队
    rear = (rear+1) % 1000;
    q[rear] = BT;
    
    while ( rear != front )
    {
        // 出队
        front = (front+1) % 1000;
        t = q[front];
        printf(" %c", t->Data);
        
        // 左子树入队列
        if (t->Left)
        {
            rear = (rear+1) % 1000;
            q[rear] = t->Left;
        }
        
        // 右子树入队列
        if (t->Right)
        {
            rear = (rear+1) % 1000;
            q[rear] = t->Right;
        }
    }
    
}

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}