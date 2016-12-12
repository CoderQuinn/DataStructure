#include <stdio.h>
#include <stdlib.h>
#define MAX 63
#define MINWEIGHT 0
typedef enum { No, Yes} Bool;

char c[MAX];
int f[MAX];

/** HuffmanTree Node **/
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    char letter;
    int weigth;
    HuffmanTree left;
    HuffmanTree right;
};
/** end **/
typedef HuffmanTree ElementType; // 指针

/** MinHeap Node **/
typedef struct Node *Heap;
struct Node
{
    ElementType elements[MAX+1]; // 指针的数组
    int size; // 堆中元素的个数
    int capacity; // 堆的最大容量
};
typedef Heap MinHeap;
/** end **/

MinHeap CreateHeap(int maxSize)
{
    ElementType temp;
    MinHeap h = (MinHeap)malloc(sizeof(struct Node));
    h->size = 0;
    h->capacity = maxSize;
    
    temp = (ElementType)malloc(sizeof(struct TreeNode));
    temp->letter = '\0';
    temp->weigth = MINWEIGHT;
    temp->left = NULL;
    temp->right = NULL;
    h->elements[0] = temp; // 哨兵，temp->weight小于堆中所有元素的值
    return h;
}

Bool IsFull(MinHeap h)
{
    return (h->size == h->capacity);
}

Bool IsEmpty(MinHeap h)
{
    return (h->size == 0);
}

Bool Insert(MinHeap h, ElementType x) // x是指针
{
    int i;
    if (IsFull(h))
        return No;
    /*
     * i首次为插入后堆中的最后一个元素的位置，也一直是x插入的当前位置；
     * 与父结点进行比较，若小于父结点，父结点下移，直到停止；
     * 由于有哨兵i=0，边界条件是停在i=1的位置。
     */
    for (i = ++h->size; x->weigth < h->elements[i/2]->weigth; i /= 2)
        h->elements[i] = h->elements[i/2];
    h->elements[i] = x;
    return Yes;
}

ElementType DeleteMin(MinHeap h)
{
    int parent, child;
    ElementType min, temp;
    if (IsEmpty(h))
        return NULL;
    
    min = h->elements[1]; // 取出堆顶元素
    temp = h->elements[h->size--]; // 堆尾赋值给temp，然后堆规模减小
    
    parent = 1; // 从堆顶开始调整
    while (parent*2 <= h->size)
    {
        child = 2*parent;
        // 寻找左右孩子结点的较小的
        if (child != h->size && h->elements[child]->weigth > h->elements[child+1]->weigth) // 是否有右孩子及是否右孩子大于左孩子
            child++;
        if (temp->weigth <= h->elements[child]->weigth) // 调整完毕
            break;
        else
            h->elements[parent] = h->elements[child];
        parent = child;
    }
    h->elements[parent] = temp;
    return min;
}

/*
 * 调整H->elements[]中的元素，使满足最大堆的有序性
 * 这里假设所有H->Size个元素已经存在H->elements[]中
 */
void PercolateDown(MinHeap h, int cur)
{
    int parent, child;
    ElementType temp;
    
    temp = h->elements[cur]; // 取出当前待调整结点的值
    
    parent = cur;
    while (parent*2 <= h->size)
    {
        child = 2*parent;
        // 寻找左右孩子结点的较小的
        if (child != h->size && h->elements[child]->weigth > h->elements[child+1]->weigth) // 是否有右孩子及是否右孩子大于左孩子
            child++;
        if (temp->weigth <= h->elements[child]->weigth) // 调整完毕
            break;
        else
            h->elements[parent] = h->elements[child];
        parent = child;
    }
    h->elements[parent] = temp;
}

/*
 * 从最后一个结点的父节点开始，直到根结点i = 1
 */
void BuildHeap(MinHeap h)
{
    int i;
    for (i = h->size/2; i > 0; i--)
        PercolateDown(h, i);
}
void ReadData(MinHeap h, int N)
{
    int i;
    ElementType temp;
    
    for (i = 0; i < N; i++)
    {
        temp = (ElementType)malloc(sizeof(struct TreeNode));
        scanf(" %c %d", &temp->letter, &temp->weigth);
        temp->left = NULL;
        temp->right = NULL;
        h->elements[++h->size] = temp;
    }
}
/** MinHeap end **/

/** HuffmanTree **/
HuffmanTree BuildHuffman(MinHeap h)
{
    int i, n;
    HuffmanTree t;
    BuildHeap(h);
    n = h->size;
    
    for (i = 1; i < n; i++)
    {
        t = malloc(sizeof(struct TreeNode));
        t->left = DeleteMin(h);
        printf("left: %c %d\n", t->left->letter, t->left->weigth);
        t->right = DeleteMin(h);
        printf("right: %c %d\n", t->right->letter, t->right->weigth);
        t->weigth = t->left->weigth + t->right->weigth;
        Insert(h, t);
    }
    t = DeleteMin(h);
    printf("%d %d",t->weigth, h->size);
    return t;
}
/** HuffmanTree end **/

int WPL(HuffmanTree t, int depth)
{
    if (!t->left && !t->right)
        return depth*t->weigth;
    else
        return WPL(t->left, depth+1)+WPL(t->right, depth+1);
}

int main()
{
    int N, wpl;
    MinHeap h;
    HuffmanTree t;
    
    scanf("%d", &N);
    h = CreateHeap(N); // 创建一个空的,容量为N的小顶堆
    ReadData(h, N);
    
    // 建立Huffman Codes树
    t = BuildHuffman(h);
    
    wpl = WPL(t, 0);
    printf("%d", wpl);
    
    return 0;
}