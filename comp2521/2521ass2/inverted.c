//
//print words and urls into invertedIndex.txt
#include <stdio.h>
#include <assert.h>
#include "readData.h"
#include "graph.h"
#include "list.h"
#include "BSTree.h"

int main(void){
    //get List_of_Urls from GetCollection( )
    List List_url = GetCollection();
    
    //get InvertedIndex from GetInvertedList (List_of_Urls)
    BSTree t = GetInvertedList(List_url);
    
    // open "invertedIndex.txt" ready for print
    FILE *invertedIndex = fopen("invertedIndex.txt","w");
    //display tree in "invertedIndex.txt"
    display_tree_a(t, invertedIndex);
    
    fclose(invertedIndex);
    //free
    freeList(List_url);
    dropBSTree(t);
    
    return 0;
}

