// from 2521 lab
// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int   vertexdegree(Graph, char *);
double   vertexIn(Graph, int);
double   vertexOut(Graph, int);
double W_in(Graph, char *, char *);
double W_out(Graph, char *, char *);



#endif
