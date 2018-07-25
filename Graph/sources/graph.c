#include "graph.h"
#include "loopQueue.h"
#include "stack.h"

AdjListGraph* createAdjListGraph()
{
    AdjListGraph* aGraph = (AdjListGraph*)malloc(sizeof(AdjListGraph));
    aGraph -> vertextNum = VERTEX_NUM;
    aGraph -> edgeNum = EDGE_NUM;

    EdgeNode* edgeNode0To1 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode0To3 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode0To4 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode1To2 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode1To4 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode2To0 = (EdgeNode*)malloc(sizeof(EdgeNode));
    EdgeNode* edgeNode3To2 = (EdgeNode*)malloc(sizeof(EdgeNode));

    edgeNode0To1 -> toAdjVex = 1;
    edgeNode0To1 -> next = edgeNode0To3;
    edgeNode0To3 -> toAdjVex = 3;
    edgeNode0To3 -> next = edgeNode0To4;
    edgeNode0To4 -> toAdjVex = 4;
    edgeNode0To4 -> next = NULL;

    edgeNode1To2 -> toAdjVex = 2;
    edgeNode1To2 -> next = edgeNode1To4;
    edgeNode1To4 -> toAdjVex = 4;
    edgeNode1To4 -> next = NULL;

    edgeNode2To0 -> toAdjVex = 0;
    edgeNode2To0 -> next = NULL;

    edgeNode3To2 -> toAdjVex = 2;
    edgeNode3To2 -> next = NULL;

    (aGraph -> adjList[0]).firstEdge = edgeNode0To1;
    (aGraph -> adjList[0]).info = 'a';
    (aGraph -> adjList[1]).firstEdge = edgeNode1To2;
    (aGraph -> adjList[1]).info = 'b';
    (aGraph -> adjList[2]).firstEdge = edgeNode2To0;
    (aGraph -> adjList[2]).info = 'c';
    (aGraph -> adjList[3]).firstEdge = edgeNode3To2;
    (aGraph -> adjList[3]).info = 'd';
    (aGraph -> adjList[4]).firstEdge = NULL;
    (aGraph -> adjList[4]).info = 'e';

    return aGraph;
}

// It just likes the preOrder traversal in binary tree
void dfsRecursion(AdjListGraph* graph, int startVertexIndex, bool visit[])
{
    printf("%c ", (graph -> adjList[startVertexIndex]).info);
     visit[startVertexIndex] = true;
    EdgeNode* edgeIndex = (graph -> adjList[startVertexIndex]).firstEdge;
    while (edgeIndex != NULL)
    {
        if (visit[edgeIndex -> toAdjVex] == false)
            dfsRecursion(graph, edgeIndex -> toAdjVex, visit);
        edgeIndex = edgeIndex -> next;
    }
}

void dfsNonRecursion(AdjListGraph* graph, int startVertextIndex, bool visit[])
{
    linked_stack* stack = NULL;
    init_stack(&stack);

    // Visit the start vertex.
    printf("%c ", (graph -> adjList[startVertextIndex]).info);
    visit[startVertextIndex] = true;
    EdgeNode* edgeNode = (graph -> adjList[startVertextIndex]).firstEdge;
    if (edgeNode != NULL)
        push(stack, edgeNode);
    while (!isEmptyStack(stack))
    {
        edgeNode = ((EdgeNode*)pop(stack)) -> next;
        while (edgeNode != NULL && !visit[edgeNode -> toAdjVex])
        {
            printf("%c ", (graph -> adjList[edgeNode -> toAdjVex]).info);
            visit[edgeNode -> toAdjVex] = true;
            push(stack, edgeNode);
            edgeNode = (graph -> adjList[edgeNode -> toAdjVex]).firstEdge;
        }
    }
}

// It's similar to the level traversal in binary tree.
void bfs(AdjListGraph* graph, int startVertexIndex, bool visit[])
{
    // Loop queue initialization.
    LoopQueue loopQ;
    loopQ.front = 0;
    loopQ.rear = 0;
    LoopQueue* loopQueue = &loopQ;
    enqueue(loopQueue, &(graph -> adjList[startVertexIndex]));
    printf("%c ", (graph -> adjList[startVertexIndex]).info);
    visit[startVertexIndex] = true;
    while (!isEmpty(loopQueue))
    {
        VertexNode* vertexNode = dequeue(loopQueue);
        EdgeNode* edgeNode = vertexNode -> firstEdge;
        while(edgeNode != NULL)
        {
            if (visit[edgeNode -> toAdjVex] == false)
            {
                printf("%c ", (graph -> adjList[edgeNode -> toAdjVex]).info);
                visit[edgeNode -> toAdjVex] = true;
                enqueue(loopQueue, &(graph -> adjList[edgeNode -> toAdjVex]));
            }
            edgeNode = edgeNode -> next;
        }
    }
}

// TODO
void prim(MGraph *graph, int startVertex)
{

}