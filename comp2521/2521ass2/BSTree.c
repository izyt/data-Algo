// from 2521 lab
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "list.h"

// make a new node containing name
BSTree newBSTree(char *name)
{
	BSTree new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->word = DUP(name);
	new->urlList = NULL;
	new->left = new->right = NULL;
	return new;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	
	List tmp = t->urlList;
	while(tmp!=NULL){
	    List delete = tmp;
	    tmp = tmp->next;
	    free(delete);
	}
	free(t->word);
	free(t);
}

// insert a new url into BSTree
BSTree BSTreeInsert(BSTree t, char *name)
{
	if (t == NULL)
		return newBSTree(name);
	else if (strcmp(name ,t->word)<0)
		t->left = BSTreeInsert(t->left, name);
	else if (strcmp(name ,t->word)>0)
		t->right = BSTreeInsert(t->right, name);
	return t;
}

// insert url to a certain word in tree
// return 1 for success, 0 for fail
int urlInsert(BSTree t, char *word, char *url)
{
    assert(t!=NULL);
    //if current t is word, insert url
    if(strcmp(t->word, word)==0){
        //if t->urlList is empty
        if(t->urlList == NULL){
            List new = malloc(sizeof(ListNode));
            new->next = NULL;
            new->name = DUP(url);
            t->urlList = new;
            return 1;
        }
        
        // else check if this url is already in list
        List tmp = t->urlList, tmp_pre = NULL;
        while(tmp!=NULL){
            if(strcmp(tmp->name, url)==0)break;
            tmp_pre = tmp;
            tmp = tmp->next;
        }
        // if not in the list 
        if(tmp==NULL){
            List new = malloc(sizeof(ListNode));
            new->next = NULL;
            new->name = DUP(url);
            tmp_pre->next = new;
        }
        return 1;
    }
    // if current t is not equal to word
    else if (strcmp(word ,t->word)<0)
		return urlInsert(t->left, word, url);
	else
		return urlInsert(t->right, word, url);
    
}

//diaplay tree in "invertedIndex.txt"
// One line per word, words should be ascending alphabetically ordered.
// Each list of urls should be ascending alphabetically ordered.
void display_tree_a(BSTree t, FILE * f){
    
    // start from far left
    if(t->left != NULL) display_tree_a(t->left, f);
    
    // present t node
    fprintf(f,"%s ",t->word);
    assert(t->urlList !=NULL);
    List tmp = t->urlList;
    while(tmp != NULL){
        fprintf(f," %s",tmp->name);
        tmp = tmp->next;
    }
    fprintf(f,"\n");
    // go to right
    if(t->right != NULL) display_tree_a(t->right, f);
    return;
}




