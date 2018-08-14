# Graph

## Representations

- adjacency list

    It is applicable to sparse graph.

    structrue definition:
    ```C
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
    ```

- adjacency martrix

    It is applicable to dense graph.

    structure definition:
    ```C
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
    ```

## Depth First Search

- Recursion

    core code:
    ```C
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
    ```
    tips: the recursive DFS is just like the preorder traversal in binary tree.

- Non-Recursion

    core code:
    ```C
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
    ```

## Breadth First Search

core code:

```C
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
```

tips:

1. The BFS is similar to the level traversal in binary tree.

2. The last node in BFS is the farthest one from the start node.

## Minimum Spanning Tree

### Prim

- algorithm

  1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.

  2. Find a node which is out of the spanning tree set and the cost between the node and the spanning tree set is minimum, and merge it into the spanning tree set.

  3. Repeat step 2 until all vertexes are in the spanning tree.

- core code

    ```C
    float prim(MGraph* graph, int startVertex)
    {
        float totalCost = 0;
        float lowCost[VERTEX_NUM];                // The value of lowCost[i] represents the minimum distance from vertex i to current spanning tree.
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
    ```

## Union Find Set

- intro

  Union-Find set(also called disjoint set), it can easily judge whether some elements are in a same set, for this feature, it plays a key role in [Kruskal's algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm) for finding the [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) of a graph.
  
  In this example, we just regard an array as sets, each index represents the element sequence number in sets, and each value in the array(i.e. array[index]) stand for the parent index of this element, and among the big sets, each set has one root, the root value is negative and its absolute value represents the number of elements. Consequently we can easily judge two elements if they are in the same set by finding their root and judging whether their root is same.

- core code:

```C
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
```

## Dijkstra Algorithm

- intro

  Dijkstra's algorithm is to find the shortest path from single node to others

- algorithm

  1. Divide into two sets: one is **visted set**, and the other is **unvisited set**, add the source node into the **visted set**.

  2. Consider all of its(i.e. source node) unvisited neighbors and select the "nearest" one, move it from unvisited set to viseted one.

  3. The new added node can be regarded as a transfer station, recalculate the distance from **unvisited set** to the source node, especially the distance through the new added node.

  4. Repeat step 2 until all the nodes are in the **visted set**.

- core code

```C
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
```

## Floyd Algorithm

- intro

  Floyd Algorithm is to find the shortest between any two nodes.

- algorithm

  1. Storing the distance between node i and node j to the ```minCost[i][j]```;
  2. Calculating the new distance if go through the node k, i.e. newDistance = minCost[i][k] + minCost[k][j]. If minCost[i][j] > newDistance, update the minCost[i][j], that is ```minCost[i][j] =  minCost[i][k] + minCost[k][j]```.
  3. Repeat the step 2 until all the nodes are traversed as the node k.

- core code

```C
void floyd(MGraph* graph)
{
    float minCost[VERTEX_NUM][VERTEX_NUM];          // Store the distance between any two nodes.
    int path[VERTEX_NUM][VERTEX_NUM];               // Store the intermediate node between the two nodes.
    int i, j, k;

    // Initialization
    for (i = 0; i < VERTEX_NUM; i++)
    {
        for (j = 0; j < VERTEX_NUM; j++)
        {
            minCost[i][j] = graph -> edges[i][j];
            path[i][j] = -1;
        }
    }

    // Find if there is another k node, it makes the distance dis[i][k] + dis[k][j] < dis[i][j];
    for (k = 0; k < VERTEX_NUM; k++)
        for (i = 0; i < VERTEX_NUM; i++)
            for (j = 0; j < VERTEX_NUM; j++)
            {
                if (minCost[i][j] > minCost[i][k] + minCost[k][j])
                {
                    minCost[i][j] = minCost[i][k] + minCost[k][j];
                    path[i][j] = k;
                }
            }

    for (i = 0; i < VERTEX_NUM; i++)
        for (j = 0; j < VERTEX_NUM; j++)
        {
            if (i != j && minCost[i][j] != MAX_COST)
                printf("%c ---> %c, the minimum cost is %f\n", (graph -> vex[i]).info, (graph -> vex[j]).info, minCost[i][j]);
        }
}
```

You can find the more detail working process information of the dijkstra algorithm from [here](https://www.cnblogs.com/nigang/p/3658990.html) 