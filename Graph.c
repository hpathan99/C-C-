//*********************************************************************************
/* Hassan Pathan, hpathan
* 2021 Spring CSE 101 pa2
* Graph.c
* Graph functions built for Graph ADT
*********************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define WHITE 0
#define BLACK 2
#define GRAY 1
#define INF -2
#define NIL -1
/*** Structs ***/
typedef struct GraphObj
{
    int *dist;
    int *parent;
    int *color;
    int source;
    int size;  //size
    int order; //order
    List *adj;
} GraphObj;

/*** Constructors-Destructors ***/

/*returns Graph pointing to a new GraphObj having n vertices*/
Graph newGraph(int n)
{
    if (n < 1)
    {
        printf("Graph Error: calling newGraph() on invalid order\n");
        exit(EXIT_FAILURE);
    }

    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc((n + 1), sizeof(List));
    G->color = calloc((n + 1), sizeof(int));
    G->parent = calloc((n + 1), sizeof(int));
    G->dist = calloc((n + 1), sizeof(int));
    G->order = n;
    G->size = 0;
    //G->adj[0] = NULL;
    G->source = NIL;

    for (int i = 1; i <= n; i++)
    {
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = WHITE;
    }
    return (G);
}
/*frees memory for Graph pG*/
void freeGraph(Graph *pG)
{
    if (pG != NULL && *pG != NULL)
    {
        for (int i = 0; i < (*pG)->order; i++)
        {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->dist);
        free((*pG)->parent);
        free((*pG)->color);
        free((*pG)->adj);

        (*pG)->adj = NULL;
        (*pG)->color = NULL;
        (*pG)->parent = NULL;
        (*pG)->dist = NULL;
        free(*pG);
        *pG = NULL;
        return;
    }
}

/*** Access functions ***/

/*returns the number of vertices of the graph*/
int getOrder(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getOrder() on Null graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->order);
}

/*returns the number of edges of the graph*/
int getSize(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getSize() on Null graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->size);
}

/*returns the most recent source vertex from BFS*/
int getSource(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getSource() on null graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->source);
}

/*returns the parent of int u*/
int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getParent() on Null graph reference\n");
        exit(EXIT_FAILURE);
    }
    else if (u < 1 || u > getOrder(G))
    {
        printf("Graph Erro: calling getParent with invalid indices.\n");
        exit(EXIT_FAILURE);
    }
    return (G->parent[u]);
}

/*returns the distance of u*/
int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph Error: calling getDist() on NULL graph reference");
        exit(EXIT_FAILURE);
    }
    else if (1 > u || u > getOrder(G))
    {
        printf("Error calling getDist(), not valid part of graph\n");
        exit(EXIT_FAILURE);
    }
    return (G->dist[u]);
}

/* */
void getPath(List L, Graph G, int u)
{
    if (getSource(G) == NIL)
    {
        printf("Error, Graph is NIL\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G))
    {
        printf("Error calling getPath(), u is not valid in graph.\n");
        exit(EXIT_FAILURE);
    }
    if (G == NULL)
    {
        printf("Graph Error: graph is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (G->source == u)
    {
        append(L, u);
    }

    else if (G->parent[u] == NIL)
    {
        append(L, NIL);
    }
    else if (G->source != NIL)
    {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }

    /*int now = u;
    append(L, now);
    while (G->parent[now] != -1)
    {
        prepend(L, G->parent[now]);
        now = G->parent[now];
    }
    if (now != getSource(G))
    {
        append(L, NIL);
    }*/
}

/*** Manipulation procedures ***/

/*makes Graph G null by setting array to NIL*/
void makeNull(Graph G)
{
    for (int i = 1; i <= getOrder(G); i++)
    {
        clear(G->adj[i]);
        G->dist[i] = INF;
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    G->size = 0;
    G->source = NIL;
}

/*places edges in adjacencies in order*/
void addEdge(Graph G, int u, int v)
{
    if (0 > u || u > getOrder(G))
    {
        printf("Graph Error: calling addEdge() at u out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    if (0 > v || v > getOrder(G))
    {
        printf("Graph Error: calling addEdge() with v out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
    //G->size++;
}

/* */
void addArc(Graph G, int u, int v)
{
    if (1 > u || u > getOrder(G))
    {
        printf("Graph Error: calling addArc() with u out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    if (1 > v || v > getOrder(G))
    {
        printf("Graph Error: calling getOrder() with v out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    List uList = G->adj[u];
    //moveFront(uList);

    while (index(uList) >= 0 && get(uList) < v)
    {
        moveNext(uList);
    }
    if (index(uList) == -1)
    {
        append(uList, v);
    }
    else
    {
        insertBefore(uList, v);
    }
    G->size++;

    /*if (length(uList) == 0)
    {
        append(uList, v);
        return;
    }
    else
    {
        set(uList, 0);
        while (index(uList) != -1)
        {
            if (v == get(uList))
            {
                return;
            }
            else if (get(uList) < v)
            {
                moveNext(uList);
            }
            else
            {
                insertBefore(uList, v);
                return;
            }
            append(uList, v);
        }
    }*/
}

void BFS(Graph G, int s)
{
    G->source = s;
    for (int i = 1; i <= getOrder(G); i++)
    {

        G->color[i] = WHITE;
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }

    G->color[s] = GRAY;
    G->dist[s] = 0;
    G->parent[s] = NIL;

    List P = newList();
    prepend(P, s);
    /*
    while (length(P) > 0)
    {
        int h = back(P);
        deleteBack(P);
        List B = G->adj[h];
        for (set(B, 0); index(B) > 0; moveNext(B))
        {
            int v = get(B);
            if (G->color[v] == WHITE)
            {
                G->color[v] = GRAY;
                G->dist[v] = G->dist[h] + 1;
                G->parent[v] = h;
                prepend(P, v);
            }
            G->color[h] = BLACK;
        }
    }*/

    for (moveFront(P); index(P) >= 0; moveNext(P))
    {
        int su = get(P);
        List otList = G->adj[su];

        for (moveFront(otList); index(otList) >= 0; moveNext(otList))
        {
            int tu = get(otList);
            if (G->color[tu] == WHITE)
            {
                G->color[tu] = GRAY;
                G->dist[tu] = G->dist[tu] + 1;
                G->parent[tu] = su;
                append(P, tu);
            }
        }
        G->color[su] = BLACK;
    }
    freeList(&P);
}

/*** Other operations ***/
void printGraph(FILE *out, Graph G)
{
    if (out == NULL || G == NULL)
    {
        printf("Graph Error: printGraph() called on NULL graph reference \n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}
