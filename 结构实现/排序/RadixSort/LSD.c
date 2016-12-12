#define MAXDIGIT 10
#define RARIX 10

typedef int ElementType;

/*** 桶元素结点 ***/
typedef struct Node *PtrToNode;
struct Node
{
    int key;
    PtrToNode next;
};

/*** 桶头结点 ***/
struct HeadNode
{
    PtrToNode head;
    PtrToNode tail;
};
typedef struct HeadNode Bucket[RARIX];

// 默认次位d=1,主位d<=MAXDIGIT
int GetDigit(int x, int D)
{
    int i, curD;
    if (x < 0)
        x = -x;
    for (i = 1; i <= D; i++)
    {
        curD = x % RARIX;
        x /= RARIX;
    }
    return curD;
}

/*** Least Significant Digit Sort, LSD ***/
void Radix_Sort(ElementType A[], int N)
{
    int i, cnt, Di, D;
    Bucket b;
    PtrToNode tmp, p, list;
    
    if (N == 1)
        return;
    list = NULL;
    // 初始化每个桶为空链表
    for (i = 0; i < RARIX; i++)
    {
        b[i].head = NULL;
        b[i].tail = NULL;
    }
    
    // 将原始序列头插法存入初始链表
    for (i = 0; i < N; i++)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->key = A[i];
        tmp->next = list;
        list = tmp;
    }
    
    // 排序
    for (D = 1; D <= MAXDIGIT; D++) // 按LSD次序处理
    {
        // 分配的过程
        p = list;
        while (p)
        {
            Di = GetDigit(p->key, D); // 当前元素的当前位数字
            // 从list中移除
            tmp = p;
            p = p->next;
            tmp->next = NULL;
            if (b[Di].head == NULL)
            {
                b[Di].head = tmp;
                b[Di].tail = tmp;
            }
            else
            {
                b[Di].tail->next = tmp;
                b[Di].tail = tmp;
            }
        }
        // 收集的过程
        list = NULL;
        // 头插入法收集
        for (Di = RARIX-1; Di >= 0; Di--)
        {
            if (b[Di].head) // 桶不为空
            {
                // 整个桶
                b[Di].tail->next = list;
                list = b[Di].head;
                b[Di].head = NULL;
                b[Di].tail = NULL;
            }
        }
    }
    // 计算负数个数
    cnt = 0;
    p = list;
    while (p)
    {
        if (p->key < 0)
            cnt++;
        p = p->next;
    }
    
    // 负数处理
    if (cnt > 0)
    {
        i = cnt-1;
        p = list;
        while (p)
        {
            if (p->key < 0)
                A[i--] = p->key;
            p = p->next;
        }
    }
    
    // 正数处理
    i = cnt;
    p = list;
    while (p)
    {
        if (p->key >= 0)
            A[i++] = p->key;
        p = p->next;
    }
    
    // 释放临时链表
    p = list;
    while (p)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}