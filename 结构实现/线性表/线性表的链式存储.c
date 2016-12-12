#include <stdio.h>
#include <stdlib.h>

typedef enum {No, Yes} Bool;

typedef struct LNode *PtrToLNode;
struct LNode
{
    int data; // 该结点元素的值
    PtrToLNode next; // 指向下一个结点的指针
};
typedef PtrToLNode List;

// 判断表是否为空
Bool IsEmpty(List L)
{
    return L->next == NULL;
}

// 初始化,建立一个n个元素且带头结点的单链线性表，头插法
List CreateList1(int n)
{
	int i;
    // 头结点的创建
    PtrToLNode header = (PtrToLNode)malloc(sizeof(struct LNode));
    header->next = NULL;
    
    for (i = 0; i <n; i++)
    {
        PtrToLNode temp= (PtrToLNode)malloc(sizeof(struct LNode)); // 生成一个新结点
        scanf("%d", &temp->data);
        temp->next = header->next;
        header->next = temp; // 头插法，新结点插入表头
    }
    return header;
}

// 初始化,建立一个n个元素且带头结点的单链线性表，尾插法
List CreateList2(int n)
{
	int i;
    // 头结点的创建
    PtrToLNode header, rear;
    header = (PtrToLNode)malloc(sizeof(struct LNode));
    header->next = NULL;
    rear = header; //指向首个尾结点，也就是头结点
    
    for (i = 0; i <n; i++)
    {
        PtrToLNode temp= (PtrToLNode)malloc(sizeof(struct LNode)); // 生成一个新结点
        scanf("%d", &temp->data);
        temp->next = NULL;
        rear->next = temp;
        rear= temp;
    }
    return header;
}
// 求表长
int Length(List L)
{
    PtrToLNode p = L->next; // 有头结点,指向第一个结点
    int i = 0;
    while (p)
    {
        p = p->next;
        i++;
    }
    return i;
}

// 查找X的指针位置
PtrToLNode Find(List L, int X)
{
    PtrToLNode p = L->next;
    while (p && p->data!=X)
        p = p->next;
    return p;
}

// 根据位序K(1≤K≤n),返回相应元素的指针 ;
PtrToLNode FindKth(List L, int K)
{
    PtrToLNode p = L;
    int i = 0;
    while (p && i<K)
    {
        p = p->next;
        i++;
    }
    if (i == K)
        return p;
    else
        return NULL;
}
/*
 插入(在第 i-1(1≤i≤n+1)个结点后插入一个值为X的新结点)
 (1)先构造一个新结点,用s指向;
 (2)再找到链表的第 i-1个结点,用p指向;
 (3)然后修改指针,插入结点 ( p之后插入新结点是 s)
 */
Bool InsertX( int X, int i, List L)
{
    PtrToLNode p, temp;
    /* 查找第i-1个结点 */
    p = FindKth(L, i-1);
    /*新结点插入在表头*/
    if (p == NULL)
    {
        printf("参数错误");
        return No;
    }
    else
    {
        temp = (PtrToLNode)malloc(sizeof(struct LNode));
        temp->data = X;
        temp->next = p->next;
        p->next = temp;
        return Yes;
    }
}

/* 在P之前插入新结点 */
Bool InsertBeforeP( List L, int X, PtrToLNode P)
{
    PtrToLNode preNode, temp;
    /* 查找P的前一个结点 */
    preNode = L;
    while (preNode->next != P)
        preNode = preNode->next;
    if (preNode == NULL) // P所指的结点不在L中
        return No;
    else
    {
        temp = (PtrToLNode)malloc(sizeof(struct LNode));
        temp->data = X;
        temp->next = P;
        preNode->next = temp;
        return Yes;
    }
    
}

// 删除表L的P结点
Bool Delete( List L, PtrToLNode P )
{
    PtrToLNode preNode, temp;
    preNode = L;
    
    // 查找p的前一个结点
    while (preNode->next!=P)
        preNode = preNode->next;
    if (preNode == NULL || P==NULL)
        return No;
    else
    {
        preNode->next = P->next;
        free(P);
        return Yes;
    }
}

Bool DeleteIth( List L, int i)
{
    PtrToLNode p = FindKth(L, i-1); // 查找第i-1个结点
    if (p == NULL || p->next == NULL) // i-1结点或i结点不存在
        return No;
    PtrToLNode temp = p->next; // temp指向第i个结点
    p->next = temp->next; // 从链表中删除
    free(temp); // 释放被删除结点
    return Yes;
}

// 遍历打印链表
void PrintList(List L)
{
    PtrToLNode p = L->next; // 有头结点
    while (p)
    {
        printf("%d", p->data);
        //        printf(" [%p] : %d ", p, p->data);
        if (p->next)
            printf("->");
        else
            printf("\n");
        p = p->next;
    }
    return;
}

// 以下为测试例子
int main()
{
    int N, k;
    printf("请输入你想创建的表长N:\n");
    scanf("%d", &N);
    printf("请输入链表中各元素:\n");
    List l = CreateList2(N);
    
    // 测试表长
    printf("表长为%d\n", Length(l));
    
    // 打印链表
    PrintList(l);
    
    /*
     测试查找X的指针位置
     PtrToLNode Find(List L, int X)
     */
    k = 3;
    PtrToLNode p1 = Find(l, k);
    printf("查找元素%d的位置为%p\n", k, p1);
    
    /*
     根据位序K(1≤K≤n),返回相应元素的指针 ;
     PtrToLNode FindKth( List L, int X)
     */
    k = 5;
    PtrToLNode p2 = FindKth(l, k);
    printf("查找第%d个元素的位置为%p\n", k, p2);
    
    // 测试插入 List InsertX( int X, int i, List L)
    InsertX(1988, 6, l);
    // 打印链表
    PrintList(l);
    
    // /* 在P1之前插入新结点 */
    InsertBeforeP(l, 2015, p1);
    // 打印链表
    PrintList(l);
    
    // 测试删除表L的p2结点
    Delete( l, p2);
    // 打印链表
    PrintList(l);
    
    // 测试删除表L的第一个结点
    DeleteIth(l, 1);
    // 打印链表
    PrintList(l);
    return 0;
}