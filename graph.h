#include <stdlib.h>
typedef int g_type;
typedef int weight_type;
typedef struct _edge
{
    int v1, v2;
    weight_type weight;
} EdgeNode, *Edge;

#define MAX_V_NUM 100
#ifndef ADJACENT_MATRIX
typedef struct _adj_node
{
    int v;
    weight_type weight;
    struct _adj_node* next;
} AdjNode;

typedef struct _v_node
{
    AdjNode* firstEdge;
    g_type data;
} VertexNode;

typedef struct _g
{
    int nV, nE;
    VertexNode* graph;
} *Graph;

Graph MakeEmptyGraph(int VertexNum);
void InsertEdgeToGraph(Graph G, Edge E);
#else
typedef struct _g
{
    int nV, nE;
    weight_type graph[MAX_V_NUM][MAX_V_NUM];
    g_type data[MAX_V_NUM];
} *Graph;

Graph MakeEmptyGraph(int VertexNum);
void InsertEdgeToGraph(Graph G, Edge E);
#endif
