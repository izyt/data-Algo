#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "graph.h"
#include "readData.h"
#include "pagerankFunction.h"

int main(int argc, char* argv[]){
    assert (argc == 4);
    // Get Collection list
    List pages = GetCollection();
    // Get graph from pages
    Graph g = GetGraph(pages);
    // calculate Page rank and insert in list
    calculatePagerank(argc, argv, pages, g);
    // reorder list by page rank
    List new_pages = order_PR(pages);
    
    //output into "pagerankList.txt"
    FILE* f = fopen("pagerankList.txt","w");
    assert(f!=NULL);
    List tmp = new_pages;
    while(tmp!=NULL){
        fprintf(f,"%s, %d, %.7lf\n",tmp->name,vertexdegree(g,tmp->name),tmp->rank);
        tmp = tmp->next;
    }
    fclose(f);
    freeList(pages);
    freeList(new_pages);
    disposeGraph(g);
    return 0;
}

