#include <stdio.h>
#define MaxN 100
int G[MaxN][MaxN]; // 邻接矩阵
int nV; // 顶点个数
int nE; // 边的个数

void BuildGraph()
{
    int i, j;
    int v1, v2, w; // 顶点<v1, v2>形成的边和权重
    scanf("%d", &nV); // 顶点的个数
    // 图的初始化
    for (i = 0; i < nV; i++)
        for (j = 0; j < nV; j++)
            G[i][j] = 0;
    
    scanf("%d", &nE); // 边的个数
    // 插入边
    for (i = 0; i < nE; i++)
    {
        scanf("%d %d %d", &v1, &v2, &w);
        G[v1][v2] = w;
        // 若是无向图，则
        G[v2][v1] = w;
    }
    
    
}
int main()
{

    
    return 0;
}