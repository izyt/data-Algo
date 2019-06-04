// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"
#include <assert.h>

#define MAX_CITY 100

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
	//if start and destination are the same place
	if(src==dest){
	    path[0] = path[1] = src;
	    return 2;
	}
	
	//BFS new Queue for BFS vertex
	Queue Q = newQueue();
	//BFS put src in Q
	QueueJoin(Q,src);
	//BFS visited and number for visited
	Vertex visited[MAX_CITY];
	//initialise
	int i;
	for(i=0; i<MAX_CITY; i++){
	    visited[i] = 0;
	}
    
	//count city in path, basicly just counting layer of each vertex 
	Vertex count_vertex[MAX_CITY];
	count_vertex[src]=0;
	//array to keep track of the path
	//for example point_back[5]=10, means BFS went from 10 to 5
	Vertex point_back[MAX_CITY];
	
	Vertex v;
	while(!QueueIsEmpty(Q)){
	    //BFS get next item in Q
	    Vertex curr = QueueLeave(Q);
	    //BFS put into visited
	    visited[curr] = 1;
	    //BFS check for any connection of v
	    for(v=0; v<g->nV; v++){
	        // if edge between surr and i && edge less than MAX allowed
	        if(g->edges[curr][v] != 0 && g->edges[curr][v] < max){
	            //BFS check if in visited
	            if(visited[v] == 0){
	                visited[v] = 1;
	                //BFS put in Q
	                QueueJoin(Q,v);
	                //keep track of path
	                point_back[v] = curr;
	                //count cities in path
	                count_vertex[v] = count_vertex[curr] + 1;
	                //check for destinction
	                if(v == dest){
	                    goto found;
	                }
	            }
	        }
	    }
	    
	}
	//not found, return 0
	return 0;
	
	found:
	//track back to src
	path[count_vertex[dest]]=dest;
	for(i = count_vertex[dest]; i > 0; i--){
	    path[i-1] = point_back[path[i]];
	}
	assert(path[0]==src);
	return count_vertex[dest]+1;

}
