#include "graph.h"

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
}
#else
Graph MakeEmptyGraph(int VertexNum)
{
    int i, j, v1, v2;
    weight_type weight;
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
    G->graph[E->V2][E->v2] = E->weight;
}
#endif
