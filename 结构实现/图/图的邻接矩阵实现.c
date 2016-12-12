#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100 // 最大顶点的个数为100
#define INFINITY 65535 // 设为双字节无符号整形的最大值

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
 * 图 结点的定义
 */
typedef struct GNode
{
    int nV; // 顶点数
    int nE; // 边数
    WeightType G[MaxVertexNum][MaxVertexNum]; // 邻接矩阵
} *PtrToGNode;
typedef PtrToGNode MGraph; // 以邻接矩阵存储的图类型

/*
 * 初始化一个有VertexNum个顶点但没有边的图
 */
MGraph CreateMgraph(int VertexNum)
{
    Vertex v, w;
    MGraph graph;
    
    graph = (MGraph)malloc(sizeof(struct GNode));
    graph->nV = VertexNum;
    graph->nE = 0;
    
    // 初始化邻接矩阵
    for (v = 0; v < graph->nV; v++)
        for (w = 0; w < graph->nV; w++)
            graph->G[v][w] = INFINITY;
    
    return graph;
}

/*
 * 边的插入
 */
void InsertEdge(MGraph graph, Edge e)
{
    // 插入边<v1, v2>
    graph->G[e->v1][e->v2] = e->weight;
    
    // 若是无向图还要插入<v2, v1>
    graph->G[e->v2][e->v1] = e->weight;
}

/*
 * 图的建立
 */
MGraph BuildGraph()
{
    MGraph graph;
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
 * 两个结点之间是否有边
 */
Bool IsEdge(MGraph graph, Vertex v, Vertex w)
{
    return graph->G[v][w] < INFINITY ? Yes : No;
}

/*
 * 访问顶点
 */
void Visit( Vertex v )
{
    printf("Visiting vertex %d\n", v);
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
 * BFS-Breadth First Search
 * 借助访问标志数组visited[]和队列
 */
void BFS(MGraph graph, Vertex x)
{ /* 以x为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue q;
    Vertex v, w;
    
    q = CreateQueue(MaxVertexNum); // 创建空队列
    
    // 访问顶点x
    Visit(x);
    visited[x] = Yes; // 标记s已访问过
    AddQ(q, x); // x入队列
    while (!IsEmpty(q))
    {
        v = DeleteQ(q); // 弹出v
        for (w = 0; w < graph->nV; w++)
        {
            if (!visited[w] && IsEdge(graph, v, w)) // 判断图中的每个顶点w，是不是v的邻接点且未访问过
            {
                Visit(w);
                visited[w] = Yes; // 标记w已访问过
                AddQ(q, w); // w入队列
            }
        }
    }
}

/*
 * DFS-Depth First Search
 * 递归版实现
 * 借助访问标志数组visited[]
 */
void DFS(MGraph graph, Vertex v)
{ /* 以v为出发点对邻接矩阵存储的图Graph进行DFS搜索 */
    Vertex w;
    
    // 访问顶点x
    Visit(v);
    visited[v] = Yes; // 标记s已访问过
    for (w = 0; w < graph->nV; w++)
        if (!visited[w] && IsEdge(graph, v, w)) // 判断图中的每个顶点w，是不是v的邻接点且未访问过
            DFS(graph, w);
}

/****************************************/

int main()
{
    MGraph g;
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

