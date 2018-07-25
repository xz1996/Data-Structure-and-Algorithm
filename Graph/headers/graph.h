#ifndef GRAPH
#define GRAPH

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---------------- macro define ---------------- */

#define VERTEX_NUM 5
#define EDGE_NUM 7

typedef char VERTEX_DATA_TYPE;

/* ---------------- struct declaration ------------ */

// Adjacency matrix (apply to dense graph)
typedef struct
{
    int number;
    VERTEX_DATA_TYPE info;
} Vertex;

typedef struct
{
    float edges[VERTEX_NUM][VERTEX_NUM];        // The value of this two dimensional array is the weight of the edge.
    int vertextNum;                             // The number of vertex.
    int edgeNum;                                // The number of edge.
    Vertex vex[VERTEX_NUM];                     // To store vertex.
} MGraph;

// Adjacency list (apply to sparse graph)
typedef struct EdgeNode
{
    int toAdjVex;                               // The index of vertex array which this edge points to.
    float weight;                               // The edge weight.
    struct EdgeNode *next;                      // The next edge, note that it only means the next edge also links to the vertex which this edge links to.
} EdgeNode;

typedef struct VertexNode
{
    VERTEX_DATA_TYPE info;                      // The vertex info,.
    struct EdgeNode* firstEdge;                 // The first edge which the vertex points to.
} VertexNode;

typedef struct
{
    VertexNode adjList[VERTEX_NUM];             // Adjacency list, which stores the all vertexes of the graph.
    int vertextNum;                             // The number of vertex.
    int edgeNum;                                // The number of edge.
} AdjListGraph;

/* ------------- method declaration -------------- */

AdjListGraph* createAdjListGraph();

void dfsRecursion(AdjListGraph* graph, int startVertexIndex, bool visit[]);

void dfsNonRecursion(AdjListGraph* graph, int startVertextIndex, bool visit[]);

void bfs(AdjListGraph* graph, int startVertexIndex, bool visit[]);

// Minimum Cost Spanning Tree
void prim(MGraph *graph, int startVertex);

#endif // GRAPH