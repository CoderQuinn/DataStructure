#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXTABLESIZE 1000000
#define KEYLENGTH 11 /* 关键词字符串的最大长度 */
#define MAXD 5
typedef char ElementType[KEYLENGTH+1]; /* 关键词类型用字符串 */
typedef int Index; /* 散列地址类型 */

/* 单链表的定义 */
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType data;
    PtrToLNode next;
    int count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/* 结束定义 */

/* 散列表的类型 */
typedef struct TblNode *HashTable;
struct TblNode // 结点的定义
{
    int tableSize; // 表的最大长度
    List heads; // 指向链表头结点的数组
};

int NextPrime(int N)
{
    int i, p;
    p = (N%2) ? N+2 : N+1; // 从大于N的下一个奇数开始
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p%i))
                break; // p不是素数
        if (i == 2) // for正常结束,说明p是素数
            break;
        else
            p += 2; // 试探下一个奇数
    }
    return p;
}

int Hash(int key, int p)
{
    return key%p;
}

HashTable CreateTable(int tableSize)
{
    HashTable h;
    int i;
    
    h = (HashTable)malloc(sizeof(struct TblNode));
    // 保证散列表最大长度是素数
    h->tableSize = NextPrime(tableSize);
    
    // 分配链表头结点数组
    h->heads = (List)malloc(h->tableSize*sizeof(struct LNode));
    // 初始化表头结点
    for (i = 0; i < h->tableSize; i++)
    {
        h->heads[i].data[0] = '\0';
        h->heads[i].next = NULL;
        h->heads[i].count = 0;
    }
    return h;
}

Position Find(HashTable h, ElementType key)
{
    Position p;
    Index pos;
    
    
    pos = Hash(atoi(key+KEYLENGTH - MAXD), h->tableSize); // 初始散列位置
    
    p = h->heads[pos].next; // 从该链表的第1个结点开始
    // 当未到表尾，并且key未找到时
    while (p && strcmp(p->data, key))
        p = p->next;
    return p;
}

int Insert(HashTable h, ElementType key)
{
    Position p, newCell;
    Index pos;
    
    p = Find(h, key);
    if (!p)
    {
        newCell = (Position)malloc(sizeof(struct LNode));
        strcpy(newCell->data, key);
        newCell->count = 1;
        pos = Hash(atoi(key+KEYLENGTH - MAXD), h->tableSize); // 初始散列位置
        // 将newCell插入为h->heads[pos]链表的第一个结点
        newCell->next = h->heads[pos].next;
        h->heads[pos].next = newCell;
        return 1;
    }
    else // 键值已存在
    {
        p->count++;
        return 0;
    }
}

void DestoryTable(HashTable h)
{
    int i;
    Position p, tmp;
    
    for (i = 0; i < h->tableSize; i++)
    {
        p = h->heads[i].next;
        while (p)
        {
            tmp = p->next;
            free(p);
            p = tmp;
        }
    }
    free(h->heads); // 释放头结点数组
    free(h); // 释放散列表结点
}

void ScanAndOutput( HashTable h)
{
    int i, maxCnt, pCnt;
    maxCnt = pCnt = 0;
    ElementType minPhone;
    List ptr;
    minPhone[0] = '\0';
    for (i = 0; i < h->tableSize; i++)
    {
        ptr = h->heads[i].next;
        while (ptr)
        {
            if (ptr->count > maxCnt)
            {
                maxCnt = ptr->count;
                strcpy(minPhone, ptr->data);
                pCnt = 1;
            }
            else if(ptr->count == maxCnt)
            {
                pCnt++;
                if (strcmp(minPhone, ptr->data) > 0)
                    strcpy(minPhone, ptr->data);
            }
            ptr = ptr->next;
        }
    }
    printf("%s %d", minPhone, maxCnt);
    if (pCnt > 1)
        printf(" %d", pCnt);
    printf("\n");
}

int main()
{
    int N, i;
    ElementType key;
    HashTable h;
    
    scanf("%d", &N);
    h = CreateTable(N*2);
    
    for (i = 0; i < N; i++)
    {
        scanf("%s", key);
        Insert(h, key);
        scanf("%s", key);
        Insert(h, key);
    }
    ScanAndOutput(h);
    DestoryTable(h);
    return 0;
}