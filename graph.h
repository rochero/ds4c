#include <stdlib.h>
#include <stdio.h>
#define ADJACENT_MATRIX
#define INFINITY 10000000
#define ERROR -1
typedef int g_type;
typedef int weight_type;
typedef int Vertex;
typedef struct _edge
{
    Vertex v1, v2;
    weight_type weight;
} EdgeNode, *Edge;

#define MAX_V_NUM 100
#ifndef ADJACENT_MATRIX
typedef struct _adj_node
{
    Vertex v;
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
} *Graph;

Graph MakeEmptyGraph(int VertexNum);
void InsertEdgeToGraph(Graph G, Edge E);
Vertex FindMinDist(Graph G, int dist[], int collected[]);
int Dijkstra(Graph G, int dist[], int path[], Vertex S);
int Floyd(Graph G, weight_type D[][MAX_V_NUM], Vertex path[][MAX_V_NUM]);

#endif
