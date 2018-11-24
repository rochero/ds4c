#include "graph.h"
#include "queue.h"
#ifndef ADJACENT_MATRIX
Graph MakeEmptyGraph(int VertexNum)
{
    int i;
    Graph G = (Graph)malloc(sizeof(struct _g));
    G->nV = VertexNum;
    G->nE = 0;
    G->graph = (VertexNode*)malloc(sizeof(VertexNode) * (G->nV));
    // index start from 0
    for (i = 0; i < G->nV; ++i)
        G->graph[i].firstEdge = NULL;
    return G;
}

void InsertEdgeToGraph(Graph G, Edge E)
{
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->v = E->v2;
    newNode->weight = E->weight;
    newNode->next = G->graph[E->v1].firstEdge;
    G->graph[E->v1].firstEdge = newNode;
    newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->v = E->v1;
    newNode->weight = E->weight;
    newNode->next = G->graph[E->v2].firstEdge;
    G->graph[E->v2].firstEdge = newNode;
    ++G->nE;
}

// Single-Source Shortest Path of Unweighted Graph
//dist[] and path[] all initialized by -1

void Unweighted(Graph G, int dist[], int path[], Vertex S)
{
    Vertex V;
    AdjNode* W;
    Queue Q = MakeEmptyQueue();
    dist[S] = 0;
    EnQueue(Q, S);
    while(!EmptyOfQueue(Q))
    {
        QNode* t = DeQueue(Q);
        V = t->data;
        for (W = G->graph[V].firstEdge; W != NULL; W = W->next)
            if (dist[W->v] == -1)
            {
                dist[W->v] = dist[V] + 1;
                path[W->v] = V;
                EnQueue(Q, W->v);
            }
    }
}

#else
Graph MakeEmptyGraph(int VertexNum)
{
    int i, j;
    Graph G = (Graph)malloc(sizeof(struct _g));
    G->nV = VertexNum;
    G->nE = 0;
    //index start from 0
    for (i = 0; i < G->nV; ++i)
        for (j = 0; j < G->nV; ++j)
            G->graph[i][j] = 0; // or INFINITY
    return G;
}

void InsertEdgeToGraph(Graph G, Edge E)
{
    G->graph[E->v1][E->v2] = E->weight;
    G->graph[E->v2][E->v1] = E->weight;
    ++G->nE;
}

// Single-Source Shortest Path of Weighted Graph
Vertex FindMinDist(Graph G, int dist[], int collected[])
{
    Vertex minV, V;
    int minDist = INFINITY;
    for (V = 0; V < G->nV; V++)
        if (!collected[V] && dist[V] < minDist)
        {
            minDist = dist[V];
            minV = V;
        }
    if (minDist < INFINITY)
        return minV;
    else
        return ERROR;
}

int Dijkstra(Graph G, int dist[], int path[], Vertex S)
{
    int collected[MAX_V_NUM];
    Vertex V, W;
    for (V = 0; V < G->nV; ++V)
    {
        dist[V] = G->graph[S][V];
        if (dist[V] < INFINITY)
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = 0;
    }
    dist[S] = 0;
    collected[S] = 1;

    while ((V = FindMinDist(G, dist, collected)) != ERROR)
    {
        collected[V] = 1;
        for(W = 0; W < G->nV; ++W)
            if (!collected[W] && G->graph[V][W] < INFINITY)
            {
                if (G->graph[V][W] < 0)
                {
                    printf("ERROR: Cannot Use Dijkstra Algorithm for Graph Exists Negative Weight\n");
                    return 0;
                }
                if (dist[V] + G->graph[V][W] < dist[W])
                {
                    dist[W] = dist[V] + G->graph[V][W];
                    path[W] = V;
                }
            }
    }
    return 1;
}
// Multi-Source Shortest Path of Graph
int Floyd(Graph G, weight_type D[][MAX_V_NUM], Vertex path[][MAX_V_NUM])
{
    Vertex i, j, k;
    for (i = 0; i < G->nV; ++i)
        for (j = 0; j < G->nV; ++j)
        {
            D[i][j] = G->graph[i][j];
            path[i][j] = -1;
        }

    for (k = 0; k < G->nV; ++k)
        for (i = 0; i < G->nV; ++i)
            for (j = 0; j < G->nV; ++j)
                if ( D[i][k] + D[k][j] < D[i][j] )
                {
                    D[i][j] = D[i][k] + D[k][j];
                    if ( i == j && D[i][j] < 0 )
                    {
                        printf("ERROR: Cannot Use Floyd Algorithm for Graph Exists Negative Weight\n");
                        return 0;
                    }
                    path[i][j] = k;
                }
    return 1;
}
#endif
