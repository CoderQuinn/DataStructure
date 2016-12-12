#include <stdio.h>
#define MINDATA -10001 /* 该值应定义为大于堆中所有可能元素的值 */
#define ERROR -1

typedef enum Bool{ No, Yes } Bool;
typedef int ElementType;

typedef struct Node
{
    ElementType *data; // 存储元素的数组
    int size; // 堆中当前元素的个数
    int capacity; // 堆的最大容量
    
} *Heap;

typedef Heap MinHeap; // 小顶堆

// 创建一个空堆
MinHeap CreateHeap(int maxSize)
{
    MinHeap h = (MinHeap)malloc(sizeof(struct Node));
    h->data = (ElementType)malloc( (maxSize+1) * sizeof(ElementType) );
    h->size = 0;
    h->capacity = maxSize;
    h->data[0] = MINDATA; // 哨兵，小于堆中所有元素的值
    
    return h;
}

Bool IsFull(MinHeap h)
{
    return (h->size == h->capacity);
}

Bool Insert(MinHeap h, ElementType x)
{
    int i;
    
    if (IsFull(h))
        return No;
    // i指向插入后堆中的最后一个元素的位置
    for (i = ++h->size; h->data[i/2] > x; i /= 2) // 与父结点比较，若小于父结点，父结点下移，直至大于父结点停止或者到i = 1停止(由于有哨兵i=0)
        h->data[i] = h->data[i/2];
    h->data[i] = x; // 将x插入
    return Yes;
}


Bool IsEmpty(MinHeap h)
{
    return (h->size == 0);
}

// 从最大堆h中取出键值为最大的元素，并删除一个结点
ElementType DeleteMin(MinHeap h)
{
    ElementType MinVal, tmp;
    int parent, child;
    
    if (IsEmpty(h))
        return ERROR;
    MinVal = h->data[1]; // 取出堆顶元素存放最大值
    tmp = h->data[h->size--]; // 当前堆的规模减小
    
    for (parent = 1; parent*2 <= h->size; parent = child)
    {
        child = parent*2;
        
        // 找左右孩子结点的最小值
        if (child != h->size && h->data[child] > h->data[child+1])
            child++; // child指向左右孩子结点的较小者
        
        if (tmp <= h->data[child]) // 找到了合适的位置
            break;
        else
            h->data[parent] = h->[child];
    }
    h->data[parent] = tmp;
    return MinVal;
}

/*
 建立最小堆:将已经存在的N个元素按最小堆的要求存放在一个一维数组中
 方法1:通过插入操作,将N个元素一个个相继插入到一个初 始为空的堆中去,其时间代价最大为O(N logN)。
 方法2:在线性时间复杂度下建立最小堆。
    (1)将N个元素按输入顺序存入,先满足完全二叉树的结构特性
    (2)调整各结点位置,以满足最小堆的有序特性。
 */

/*
 * 调整H->Data[]中的元素，使满足最大堆的有序性
 * 这里假设所有H->Size个元素已经存在H->Data[]中
 */

void PercolateDown(MinHeap h, int p)
{
    int parent, child;
    ElementType x;
    
    x = h->data[p]; // 取出根结点存放的值
    for (parent = p; parent*2 <= h->size; parent = child)
    {
        child = parent*2;
        
        // 找左右孩子结点的最小值
        if (child != h->size && h->data[child] > h->data[child+1])
            child++; // child指向左右孩子结点的较小者
        
        if (tmp <= h->data[child]) // 找到了合适的位置
            break;
        else
            h->data[parent] = h->[child];
    }
    h->data[parent] = x;
}

void BuildHeap(MinHeap h)
{
    int i;
    // 从最后一个结点的父节点开始，直到根结点i = 1
    for (i = h->size/2; i > 0; i--)
        PercolateDown(h, i);
}