// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
    if (L->nitems < 2)return peaksL;
 struct DLListNode *temp = L->first->next;
 int num_p, mid,num_n;
 for (;temp->next != NULL;temp = temp->next){
     num_p = temp->prev->value;
     mid = temp->value;
     num_n = temp->next->value;
     if(num_p < mid && mid > num_n){
         DLListNodeP nw = newDLListNode(mid);
         if(peaksL->first == NULL){
             peaksL->first = peaksL->curr =peaksL->last = nw;
          } else {
             peaksL->curr->next = peaksL->last = nw;
             nw->prev = peaksL->curr;
         
             peaksL->curr = peaksL->curr->next; 
          }        
        }
    }
    
    
	return peaksL;
}
