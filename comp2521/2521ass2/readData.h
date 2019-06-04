#ifndef READ_DATA_H
#define READ_DATA_H

#include "graph.h"
#include "BSTree.h"
#include "list.h"


//#ifndef READDATA_H
//#define READDATA_H

// Create a set (list) of urls to process 
// by reading data from file "collection.txt"
List GetCollection();


//return number of Lists in List linklist
int List_num(List url);

// Create empty graph (use graph ADT in say graph.h and graph.c)
// For each url in the above list, read <url>.txt file
// and update graph by adding a node and outgoing links
Graph GetGraph(List url);

// Create empty inverted list
// For each url in List_of_Urls
//read <url>.txt file, and update inverted index
BSTree GetInvertedList(List url);

void modify_words(char *word);




#endif // READ_DATA_H
