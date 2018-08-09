#include "graph.h"

void printGraph()
{
    printf("-----------> c <----------\n");
    printf("|            |           |\n");
    printf("|            |           |\n");
    printf("|            V           |\n");
    printf("b <--------- a --------> d\n");
    printf("|            |            \n");
    printf("|            |            \n");
    printf("|            V            \n");
    printf("-----------> e\n");
}

void clearVisitFlag(bool visit[])
{
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        visit[i] = false;
    }
}

int main()
{
    AdjListGraph* adjListGraph = createAdjListGraph();
    printGraph();

    /* -------------------------- Recursion Depth First Search -----------------------------*/
    printf("Recursion Depth First Search :\n");
    bool visit[VERTEX_NUM];
    clearVisitFlag(visit);
    // Ensure that all vertex was visited.
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        if (visit[i] == false)
            dfsRecursion(adjListGraph, i, visit);
    }
    printf("\n");

    /* -------------------------- Non-Recursion Depth First Search -----------------------------*/
    printf("Non-Recursion Depth First Search :\n");
    clearVisitFlag(visit);
    // Ensure that all vertex was visited.
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        if (visit[i] == false)
            dfsNonRecursion(adjListGraph, i, visit);
    }
    printf("\n");

    /* -------------------------- Breadth Depth First Search -----------------------------*/
    printf("Breadth First Search :\n");
    clearVisitFlag(visit);
    // Ensure that all vertex was visited.
    for (int i = 0; i < VERTEX_NUM; i++)
    {
        if (visit[i] == false)
            bfs(adjListGraph, i, visit);
    }
    printf("\n");

    /* -------------------------- Minimum Spanning Tree -----------------------------*/
    printf("Prim Algorithm : \n");
    MGraph* mGraph = createMatrixGraph();
    // Print the cost of each edge.
    for (int i = 0; i < VERTEX_NUM; i++)
        for (int j = i + 1; j < VERTEX_NUM; j++)
            if ((mGraph -> edges[i][j]) != MAX_COST)
                printf("%c---%c, cost:%f\n", (mGraph -> vex[i]).info, (mGraph -> vex[j]).info, mGraph -> edges[i][j]);
    float totalCost = prim(mGraph, 0);
    printf("\n");

    printf("The minimum cost is %f\n", totalCost);
    printf("\n");

    return 0;
}
