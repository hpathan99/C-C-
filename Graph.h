/*********************************************************************************
* Hassan Pathan, hpathan
* 2021 Spring CSE 101 pa2
* Graph.h
* Graph function declarations for Graph ADT
*********************************************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#define INF -2
#define NIL -1

typedef struct GraphObj *Graph;
typedef struct ListObj *List;
/*** Constructors-Destructors ***/

Graph newGraph(int n);
void freeGraph(Graph *pG);

/*** Access functions ***/

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE *out, Graph G);

#endif