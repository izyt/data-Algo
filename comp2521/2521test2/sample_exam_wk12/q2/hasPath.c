
/* hasPath.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"



/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/


//int visited*;  // array of visited

int hasPath(Graph g, Vertex src, Vertex dest)
{
    //list is a queue for what to visit next
    //visited is to mark if a vertex has been visited
    int list[g->nV],visited[g->nV],num=1;
    int i;
    for(i=0;i<g->nV;i++){
        visited[i]=0;
        list[i]=0;
    }
    list[0]=src;
    visited[src]=1;
    for(i=0; i<num; i++){
        int j;
        for(j=0; j<g->nV; j++){
            if(g->edges[list[i]][j]>0 && visited[j]==0){
                list[num]=j;
                num++;
                visited[j]++;
                if(j==dest)return 1;
            }
        }
    }
    return 0;
}
