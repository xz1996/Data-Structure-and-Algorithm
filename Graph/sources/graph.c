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

MGraph* createMatrixGraph()
{
    MGraph* mGraph = (MGraph*)malloc(sizeof(MGraph));
    mGraph -> edgeNum = EDGE_NUM;
    mGraph -> vertextNum = VERTEX_NUM;
    (mGraph -> vex[0]).info = 'a';
    (mGraph -> vex[1]).info = 'b';
    (mGraph -> vex[2]).info = 'c';
    (mGraph -> vex[3]).info = 'd';
    (mGraph -> vex[4]).info = 'e';

    for (int i = 0; i < VERTEX_NUM; i++)
        for (int j = 0; j < VERTEX_NUM; j++)
            if (i == j)
                mGraph -> edges[i][j] = 0;
            else
                mGraph -> edges[i][j] = MAX_COST;

    mGraph -> edges[0][1] = 10;
    mGraph -> edges[1][0] = 10;
    mGraph -> edges[0][2] = 40;
    mGraph -> edges[2][0] = 40;
    mGraph -> edges[0][3] = 8;
    mGraph -> edges[3][0] = 8;
    mGraph -> edges[0][4] = 36;
    mGraph -> edges[4][0] = 36;
    mGraph -> edges[1][4] = 5;
    mGraph -> edges[4][1] = 5;
    mGraph -> edges[2][3] = 30;
    mGraph -> edges[3][2] = 30;

    return mGraph;
}

// It's just like the preOrder traversal in binary tree
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


float prim(MGraph* graph, int startVertex)
{
    float totalCost = 0;
    float lowCost[VERTEX_NUM];              // The value of lowCost[i] represents the minimum distance from vertex i to current spanning tree.
    bool treeSet[VERTEX_NUM];               // The value of treeSet[i] represents whether the vertex i has been merged into the spanning tree.

    // Initialization
    for (int i = 0; i < (graph -> vertextNum); i++)
    {
        lowCost[i] = graph -> edges[startVertex][i];        // Init all cost from i to startVertex.
        treeSet[i] = false;                                 // No vertex is in the spanning tree set at first.
    }

    treeSet[startVertex] = true;                            // Merge the startVertex into the spanning tree set.
    printf("%c ", (graph -> vex[startVertex]).info);
    for (int i = 0; i < (graph -> vertextNum); i++)
    {
        int minCost = MAX_COST;                             // MAX_COST is a value greater than any other edge weight.
        int newVertex = startVertex;

        // Find the minimum cost vertex which is out of the spanning tree set.
        for (int j = 0; j < (graph -> vertextNum); j++)
        {
            if (!treeSet[j] && lowCost[j] < minCost)
            {
                minCost = lowCost[j];
                newVertex = j;
            }
        }
        treeSet[newVertex] = true;                          // Merge the new vertex into the spanning tree set.

        /*

            Some ops, for example you can print the vertex so you will get the sequence of node of minimum spanning tree.

        */
        if (newVertex != startVertex)
        {
            printf("%c ", (graph -> vex[newVertex]).info);
            totalCost += lowCost[newVertex];
        }


        // Judge whether the cost is change between the new spanning tree and the remaining vertex.
        for (int j = 0; j < (graph -> vertextNum); j++)
        {
            if (!treeSet[j] && lowCost[j] > graph -> edges[newVertex][j])
                lowCost[j] = graph -> edges[newVertex][j];  // Update the cost between the spanning tree and the vertex j.
        }
    }
    return totalCost;
}

int findRootInSet(int array[], int x)
{
    if (array[x] < 0)
    {
        // Find the root index.
        return x;
    }
    else
    {
        // Recursively find its parent until find the root,
        // then recursively update the children node so that they will point to the root.
        return array[x] = findRootInSet(array, array[x]);
    }
}

bool unionSet(int array[], int node1, int node2)
{
    int root1 = findRootInSet(array, node1);
    int root2 = findRootInSet(array, node2);
    if (root1 == root2)
    {
        // It means they are in the same set
        return false;
    }

    // The value of array[root] is negative and the absolute value is its children numbers,
    // when merging two sets, we choose to merge the more children set into the less one.
    if (array[root1] > array[root2])
    {
        array[root1] += array[root2];
        array[root2] = root1;
    }
    else
    {
        array[root2] += array[root1];
        array[root1] = root2;
    }
    return true;
}

int getSetNumsInUFS(int array[], int arraySize)
{
    int count = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] < 0)
            count++;
    }
    return count;
}

void dijkstra(MGraph* graph, int startVertexIndex)
{
    // For storing the minimum cost from the arbitrary node to the start vertex.
    float minCostToStart[VERTEX_NUM];

    // For marking whether the node is in the set.
    bool set[VERTEX_NUM];

    // Initialization
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        minCostToStart[i] = graph -> edges[i][startVertexIndex];
        set[i] = false;
    }

    // Add the start vertex into the set.
    set[startVertexIndex] = true;
    int minNodeIndex = startVertexIndex;

    for (int count = 1; count < VERTEX_NUM; count++)
    {
        int minCost = MAX_COST;

        // Find the adjacent node which is nearest to the startVertexIndex.
        for (int i = 0; i < VERTEX_NUM; i++)
        {
            if (!set[i] && minCostToStart[i] < minCost)
            {
                minNodeIndex = i;
                minCost = minCostToStart[minNodeIndex];
            }
        }

        // Add the proper node into the set
        set[minNodeIndex] = true;

        // After the new node is added into the set, update the minimum cost of each node which is out of the set.
        for (int i = 0; i < VERTEX_NUM; i++)
        {
            if (!set[i] && (graph -> edges[i][minNodeIndex]) < MAX_COST)
            {
                // The new cost of each node to source = the cost of new added node to source + the cost of node i to new added node.
                float newCost = minCostToStart[minNodeIndex] + graph -> edges[i][minNodeIndex];

                if (newCost < minCostToStart[i])
                    minCostToStart[i] = newCost;
            }
        }
    }

    printf("The cost of %c to each node:\n", (graph -> vex[startVertexIndex]).info);
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        if (i != startVertexIndex)
            printf("-----> %c : %f\n", (graph -> vex[i]).info, minCostToStart[i]);
    }
}
