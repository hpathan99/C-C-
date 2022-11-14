//-----------------------------------------------------------------------------
//Hassan Pathan
// GraphTest.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[])
{
    int i, d, p, max, min, n = 35;
    List C = newList(); // central vertices
    List P = newList(); // peripheral vertices
    List E = newList(); // eccentricities
    Graph G = NULL;

    // Build graph G
    G = newGraph(n);
    for (i = 1; i < n; i++)
    {
        if (i % 7 != 0)
            addEdge(G, i, i + 1);
        if (i <= 28)
            addEdge(G, i, i + 7);
    }
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    addEdge(G, 14, 33);
    printf("Graph: \n");
    // Print adjacency list representation of G
    printGraph(stdout, G);

    printf("The order of graph is: %d\n", getOrder(G));

    printf("The size of the graph is: %d\n", getSize(G));

    for (p = 1; p <= n; p++)
    {
        BFS(G, p);
        max = getDist(G, 1);
        for (i = 2; i <= n; i++)
        {
            d = getDist(g, i);
            max = (max < d ? d : max);
        }
        append(E, max);
    }

    Graph S = newGraph(200);
    int j = 0;
    for (j = 1; j < 200; ++j)
    {
        if (j % 2 == 1)
            addEdge(S, j, 200 - j);
        else if (j % 3 == 1)
            addArc(S, j, 200 - j);
    }

    for (i = 1; i < 200; ++i)
    {
        BFS(S, i);
        for (j = 1; j < 200; ++j)
        {
            int d = getDist(S, j);
            if (d != INF)
                printf("Dist %d-%d: %d\n", i, j, d);
        }
    }

    BFS(S, 10);
    List N = newList();
    getPath(N, S, 190);
    printf("Path from 10 to 190: ");
    printList(stdout, N);
    printf("\n");

    BFS(S, 101);
    List Q = newList();
    getPath(Q, S, 99);
    printf("Path from 101 to 99: ");
    printList(stdout, Q);
    printf("\n");

    freeList(&N);
    freeList(&Q);
    freeList(&C);
    freeList(&P);
    freeList(&E);
    freeGraph(&S);
    freeGraph(G);
    freeGraph(&G);
    return (0);
}