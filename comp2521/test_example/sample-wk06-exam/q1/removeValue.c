// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value){
    //empty list
    if(L==NULL)return;
    
    DLListNodeP temp = L -> first;
    
    for(temp=L->first; temp->next!=NULL; temp = temp){
        if(temp->value == value){
            if(temp==L->first){
                temp = temp->next;
                free(L->first);
                L->first = temp;
                temp->prev = NULL;
            }else{
                L->curr = temp;
                temp->prev->next = temp->prev->next->next;
                temp->next->prev = temp->next->prev->prev;
                temp = temp->next;
                free(L->curr);
            }
            L->nitems--;
        }else{
            temp = temp->next;
        }
    }
    if(temp->value == value){
        if(L->nitems == 1){
            free(temp);
            L->first=NULL;
            L->last=NULL;
        }else{
            temp = temp->prev;
            free(L->last);
            L->last = temp;
            temp->next=NULL;
        }
        L->nitems--;
    }
    L->curr = L->first;
	return;
}
