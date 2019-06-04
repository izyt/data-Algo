
#ifndef LIST_H
#define LIST_H

#include <stdio.h>

//Link List
typedef struct ListNode *List;

typedef struct ListNode{
    char   *name;
    double rank;
    List   next;
    int    times;//for SearchPageRank
}ListNode;

//Tree 
typedef struct BSTNode *BSTree;

typedef struct BSTNode {
	char *word;
	ListNode *urlList;
	BSTree left, right;
} BSTNode;

char *DUP(char* s);
char *SEP(char **str, const char *delims);
void freeList(List l);
#endif // LIST_H
