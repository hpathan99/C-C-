/*********************************************************************************
* Hassan Pathan, hpathan
* 2021 Spring CSE 101 pa2
* 
*********************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

/*void printPath(Graph G, int u, int v, List L, FILE *out)
{
    getPath(L, G, v);
    if (v == -1)
    {
        fprintf(out, "\n");
        fprintf(out, "The distance from %d to %d is infinity", getSource(G), v);
        fprintf(out, "No %d-%d path exists\n", getSource(G), v);
    }
    else
    {
        fprintf(out, "\n");
        fprintf(out, "The distance from %d to %d is %d\n", getSource(G), v, getDist(G, v));
        fprintf(out, "A shortest %d-%d path is: ", getSource(G), v);
        printList(out, L);
        fprintf(out, "\n");
        clear(L);
    }
}*/

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    int src;
    int dest;
    int numOfVertex = 0;

    //checking for incorrect arguments
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading. \n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Unable to open file %s for writing. \n", argv[2]);
        exit(EXIT_FAILURE);
    }

    //getting number of vertices
    fscanf(in, "%d", &numOfVertex);
    //new graph for the vertices
    Graph nG = newGraph(numOfVertex);

    int vertex1;
    int vertex2;
    //getting coordinates of the graph then make it
    while (fscanf(in, "%d %d", &vertex1, &vertex2))
    {

        if (vertex1 == 0 && vertex2 == 0)
        {
            break;
        }
        //add vetex to other vertex
        addEdge(nG, vertex1, vertex2);
    }

    //print graph to out file
    printGraph(out, nG);
    //fprintf(out, "\n");

    //using destination with same loop as before
    List L = newList();
    while (fgetc(in) != EOF)
    {
        fscanf(in, "%d", &src);
        fscanf(in, "%d", &dest);

        if (src == 0 && dest == 0)
        {
            break;
        }

        BFS(nG, src);

        int finalDistance = getDist(nG, dest);
        getPath(L, nG, dest);

        if (getDist(nG, dest) == INF)
        {
            //fprintf(out, "The distance from %d to %d is %d\n", src, dest, length(L) - 1);
            fprintf(out, "The distance from %d to %d is %d\n", src, dest, finalDistance);
            //fprintf(out, "A shortest %d-%d path is: ", src, dest);
            fprintf(out, "No %d-%d path exists\n\n", src, dest);
            //printList(out, L);
            //fprintf(out, "\n\n");
        }
        else
        {
            fprintf(out, "The distance from %d to %d is infinity \n", src, dest);
            fprintf(out, "A shortest %d-%d path is: ", src, dest);
            //fprintf(out, "No %d-%d path exists\n\n", src, dest);
            printList(out, L);
            fprintf(out, "\n");
        }
        freeList(&L);
    }

    freeGraph(&nG);
    fclose(out);
    fclose(in);
    return 0;
}