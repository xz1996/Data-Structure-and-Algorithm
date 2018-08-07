#ifndef GRAPH
#define GRAPH

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---------------- macro define ---------------- */

#define VERTEX_NUM 5
#define EDGE_NUM 7

#define MAX_COST 65535

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

MGraph* createMatrixGraph();

void dfsRecursion(AdjListGraph* graph, int startVertexIndex, bool visit[]);

void dfsNonRecursion(AdjListGraph* graph, int startVertextIndex, bool visit[]);

void bfs(AdjListGraph* graph, int startVertexIndex, bool visit[]);

// Minimum Cost Spanning Tree

/**
 *  Prim Algorithm
 *
 *  Time complexity : O(n^2).
 *
 *  Prim algorithm is applicable to dense graph to generate minimum spanning tree.
 */
float prim(MGraph* graph, int startVertex);


// Union Find Set

/**
 * Find the root index in a set.
 *
 * Note that there are some divided sets in the array, and each set has one root, the rest of the nodes in this set is its descendants.
 *
 * @param array, the set array.
 * @param x, the node that you want to find its root.
 * @return the root index in the array.
 */
int findRootInSet(int array[], int x);

/**
 * Merge two sets by their root.
 *
 * @param array, the set array.
 * @param node1, the root node in one set.
 * @param node2, the root node in another set.
 * @return whether the operation is success.
 */
bool unionSet(int array[], int node1, int node2);

int getSetNumsInUFS(int array[], int arraySize);

#endif // GRAPH