//from 2521 lab
// BSTree.h ... interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

#include "list.h"

// make a new node containing name
BSTree newBSTree(char *name);

// free memory associated with BSTree
void dropBSTree(BSTree t);

// insert a new url into BSTree
BSTree BSTreeInsert(BSTree t, char *name);

// insert url to a certain word in tree
// return 1 for success, 0 for fail
int urlInsert(BSTree t, char *word, char *url);

//diaplay tree in "invertedIndex.txt"
// One line per word, words should be ascending alphabetically ordered.
// Each list of urls should be ascending alphabetically ordered.
void display_tree_a(BSTree t, FILE * f);

#endif

