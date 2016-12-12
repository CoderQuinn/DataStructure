#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

typedef struct Node LNode;
struct Node
{
    int data;
    int next;
};
typedef LNode *List;
LNode nodes[MAX];


// 带头结点的静态链表，头结点的data记录有效总结点数，next为第一个结点的下标位置
List ListRead(int N, int addr)
{
    int i, cnt, t;
    int address, data, next;
    List l;
    for (i = 0; i < N; i++)
    {
        scanf("%d %d %d", &address, &data, &next);
        nodes[address].data = data;
        nodes[address].next = next;
    }
    
    cnt = 0;
    t = addr;
    // 统计有效的结点
    while (t != -1)
    {
        t = nodes[t].next;
        cnt++;
    }
    l = (List)malloc(sizeof(LNode));
    l->data = cnt;
    l->next = addr;
    return l;
}

List ListReserve(List l, int K)
{
    int i, j, N;
    int pre, cur, tmp;
    int thisKTail, lastKTail;
    
    thisKTail = -1;
    N = l->data;
    cur = l->next;
    tmp = nodes[cur].next;
    for (i = 0; i<N/K; i++)
    {
        pre = -1;
        lastKTail = thisKTail;
        thisKTail = cur;
        for (j = 0; j < K; j++)
        {
            nodes[cur].next = pre;
            pre = cur;
            cur = tmp;
            tmp = nodes[tmp].next;
        }
        if (i == 0)
            l->next = pre;
        else
            nodes[lastKTail].next = pre;
    }
    nodes[thisKTail].next = cur;
    return l;
}

void OutPut(List l)
{
    int t;
    t = l->next;
    while (nodes[t].next != -1)
    {
        printf("%05d %d %05d\n", t, nodes[t].data, nodes[t].next);
        t = nodes[t].next;
    }
    printf("%05d %d %d", t, nodes[t].data, nodes[t].next);
}

int main()
{
    int next, N, K;
    List l;
    
    scanf("%d %d %d", &next, &N, &K);
    l = ListRead(N, next);
    l = ListReserve(l, K);
    OutPut(l);
    return 0;
}