#ifndef PAGERANKFUNCTION_H
#define PAGERANKFUNCTION_H

#include "readData.h"
#include "list.h"
#include "graph.h"


//calculate pagerank
void calculatePagerank(int n, char* sti[], List pages, Graph g);

// reorder list by pagerank decending
// return a new list without changing the previous list
List order_PR(List URL);

// insert list node by pagerank decending
List insert_list_by_PR(List pre_l, List new_node);


#endif
