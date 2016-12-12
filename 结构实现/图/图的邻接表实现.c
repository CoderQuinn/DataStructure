/* 图的邻接表表示法 */
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100 // 最大顶点数设为100

/******************** 队 列 ********************/
#define ElementType int
typedef enum { No,Yes } Bool;
typedef int Position;
typedef struct QNode *PtrToQNode;
struct QNode
{
    ElementType *data; // 存储元素的数组
    Position rear; // 队列的尾指针
    Position front; // 队列的头指针
    int maxSize; // 队列的最大容量
};
typedef PtrToQNode Queue;

Queue CreateQueue(int maxSize)
{
    Queue q = (Queue)malloc(sizeof(struct QNode));
    q->data = (ElementType *)malloc(sizeof(ElementType));
    q->front = q->rear = 0;
    q->maxSize = maxSize;
    return q;
}

Bool IsFull(Queue q)
{
    return ((q->rear+1)%q->maxSize == q->front);
}

Bool AddQ(Queue q, ElementType x)
{
    if (IsFull(q))
        return No;
    q->rear = (q->rear+1)%q->maxSize;
    q->data[q->rear] = x;
    return Yes;
}

Bool IsEmpty(Queue q)
{
    return (q->front == q->rear);
}

ElementType DeleteQ(Queue q)
{
    if (IsEmpty(q))
    {
        printf("队列空\n");
        return No;
    }
    else
    {
        q->front = (q->front+1)%q->maxSize;
        return q->data[q->front];
    }
}
/****************************************/

/******************** 图 ********************/
int visited[MaxVertexNum] = {0};
typedef int Vertex; // 用顶点下标表示顶点，类型为整型
typedef int WeightType; // 边的权值设为整型

/*
 * 图 边的定义
 */
typedef struct ENode
{
    Vertex v1, v2; // 有向边<v1, v2>
    WeightType weight; // 边的权重
} *PtrToENode;
typedef PtrToENode Edge;

/*
 * 边表中邻接点的定义
 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex adjV; // 邻接点下标
    WeightType weight; // 边权重
    PtrToAdjVNode next; // 指向下一个邻接点的指针
};

/*
 * 顶点表头结点的定义
 */
struct Vnode
{
    PtrToAdjVNode firstEdge; // 边表头指针
};
typedef struct Vnode AdjList[MaxVertexNum]; // AdjList是邻接表类型

/*
 * 图结点的定义
 */
struct GNode
{
    int nV; // 顶点数
    int nE; // 边数
    AdjList G; // 邻接表
};
typedef struct GNode *PtrToGNode;
typedef PtrToGNode LGraph; // 以邻接表方式存储的图类型

/*
 * 初始化一个有VertexNum个顶点但没有边的图
 */
LGraph CreateMgraph(int VertexNum)
{
    Vertex v;
    LGraph graph;
    
    graph = (LGraph)malloc(sizeof(struct GNode)); // 建立图
    graph->nV = VertexNum;
    graph->nE = 0;
    
    // 初始化邻接表头指针
    for (v = 0; v < graph->nV; v++)
        graph->G[v].firstEdge = NULL;
    return graph;
}

/*
 * 边的插入
 */
void InsertEdge( LGraph graph, Edge e)
{
    PtrToAdjVNode newNode;
    
    // 插入边<v1, v2>
    // 为v2建立新的邻接点
    newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    newNode->adjV = e->v2;
    newNode->weight = e->weight;
    // 将v2插入v1的表头,头插法
    newNode->next = graph->G[e->v1].firstEdge;
    graph->G[e->v1].firstEdge = newNode;
    
    // 若是无向图，还要插入边<v2, v1>
    newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    newNode->adjV = e->v1;
    newNode->weight = e->weight;
    // 将v1插入v2的表头,头插法
    newNode->next = graph->G[e->v2].firstEdge;
    graph->G[e->v2].firstEdge = newNode;
}

/*
 * 图的建立
 */
LGraph BuildGraph()
{
    LGraph graph;
    Edge e;
    Vertex x;
    int nV, i;
    
    printf("请输入顶点的个数\n");
    scanf("%d", &nV); // 读入顶点的个数
    graph = CreateMgraph(nV); // 初始化有nV个顶点但没有边的图
    
    printf("请输入边的个数\n");
    scanf("%d", &graph->nE); // 读入边的个数
    if (graph->nE) // 如果有边
    {
        e = (Edge)malloc(sizeof(struct ENode)); // 建立边结点
        printf("请输入丙个顶点的序号和权值,格式为:v1 v2 w\n");
        // 读入边，格式为“起点 终点 权重”, 插入邻接矩阵
        for (i = 0; i < graph->nE; i++)
        {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            InsertEdge(graph, e);
        }
    }
    
    return graph;
}

/*
 * 初始化未访问标志
 */
void InitVisited()
{
    int i;
    for (i = 0; i < MaxVertexNum; i++)
        visited[i] = No;
}

/*
 * 访问顶点
 */
void Visit( Vertex v )
{
    printf("Visiting vertex %d\n", v);
}

/*
 * DFS-Depth First Search
 * 递归版实现
 * 借助访问标志数组visited[]
 */
void DFS(LGraph graph, Vertex x)
{ /* 以x为出发点对邻接表存储的图Graph进行DFS搜索 */
    PtrToAdjVNode v;
    
    // 访问顶点v
    Visit(x);
    visited[x] = Yes; // 标记s已访问过
    
    v = graph->G[x].firstEdge; // 以顶点表v下标对应的边表的头结点
    while (v) // 对v的每个邻接点
    {
        if (!visited[v->adjV])
            DFS(graph, v->adjV);
        v = v->next;
    }

}

/*
 * BFS-Breadth First Search
 * 借助访问标志数组visited[]和队列
 */
void BFS(LGraph graph, Vertex x)
{
    Queue q;
    Vertex v;
    PtrToAdjVNode w;
    
    q = CreateQueue(MaxVertexNum);
    
    // 访问顶点x
    Visit(x);
    visited[x] = Yes; // 标记s已访问过
    AddQ(q, x); // x入队列
    while (!IsEmpty(q))
    {
        v = DeleteQ(q); // 弹出v
        w = graph->G[v].firstEdge;
        while (w)
        {
            if (!visited[w->adjV])
            {
                Visit(w->adjV);
                visited[w->adjV] = Yes;
                AddQ(q, w->adjV); // 入队列
            }
            w = w->next;
        }
    }
    
}
/****************************************/

int main()
{
    LGraph g;
    Vertex x;
    g = BuildGraph();
    printf("请输入BFS的起始访问点:\n");
    scanf("%d", &x);
    BFS(g, x);
    
    InitVisited(); // 访问数组置为未访问
    
    printf("请输入DFS的起始访问点:\n");
    scanf("%d", &x);
    DFS(g, x);
    return 0;
}