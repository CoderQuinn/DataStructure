#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define Maxsize 100

typedef enum {NO, YES} BOOL;
// ￼定义一个LNode,利用数组的连续存储空间顺序存放线性表的各元素
struct LNode
{
    ElementType data[Maxsize];
    int last;
};
// 定义一个List的指针指向LNode的数组结点
typedef struct LNode *List;

// 初始化,建立空的顺序表
List makeEmpty()
{
    List l;
    l = (List)malloc(sizeof(struct LNode));
    l->last = -1;
    return l;
}

// 求表长
int length(List l)
{
    return l->last+1;
}

// 查找X
int find(List l, ElementType x)
{
    int i = 0;
    while (i <= l->last && l->data[i]!=x)
        i++;
    if (i > l->last) // 若没有找到，返回ERROR
        return NO;
    else
        return i;
}

// 根据位序K,返回相应元素 ;
ElementType findKth(int k, List l)
{
    if (k<0 || k>l->last+1)
    {
        printf("查找失败");
        return NO;
    }
    return l->data[k];
}

/* 在L的指定位置P前插入一个新元素X */
int insert( List l, ElementType x, int p)
{
    int i;
    
    // 判断是否表满
    if (l->last >(Maxsize-1))
    {
        printf("表满");
        return NO;
    }
    
    // 判断位置是否合法
    if (p<0 || p>l->last+1)
    {
        printf("插入位置不合法");
        return NO;
    }
    
    // 将位置p及以后的位置顺序向后移动
    for (i = l->last; i>=p; i--)
        l->data[i+1] = l->data[i];
    l->data[p] = x; // 新元素插入
    l->last++; // Last仍指向最后元素
    printf("插入成功\n");
    return YES;
}

// 删除表L的第 P (0≤i≤n-1)个位置上的元素
int delete( List l, int p )
{
    int i;
    // 检查删除位置的合法性
    if (p<0 || p>l->last)
    {
        printf("位置%d不存在元素\n", p);
        return NO;
    }
    // 将位置P+1有以后的元素顺序向前移动
    for ( i = p+1; i<=l->last; i++)
        l->data[i-1] = l->data[i];
    l->last--; // Last仍指向最后元素
    printf("删除成功\n");
    return YES;
}

// 以下为测试例子
int main()
{
    List l = makeEmpty();
    for (int i = 0; i<10; i++)
    {
        l->data[i] = i+1;
        l->last++;
    }
    // 测试表长
    printf("表长为%d\n", length(l));
    
    // 测试查找
    int a = find(l, 9);
    printf("查找9的位置为%d\n", a);
    
    // 测试插入
    int b = insert(l, 188, 5);
    printf("插入结果的返回值%d\n", b);
    
    // 测试查找位序
    int c = findKth(5, l);
    printf("查找下标5的元素为%d\n", c);
    
    // 测试删除
    int d = delete(l, 9);
    printf("删除下标9元素的结果的返回值%d\n", d);
    
    for (int i =0; i<=l->last; i++)
        printf("%d ", l->data[i]);
    
    return 0;
}