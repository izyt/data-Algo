#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "readData.h"
#include "list.h"
#include "graph.h"
#include "pagerankFunction.h"


void calculatePagerank(int n, char* str[], List pages, Graph g){
      //get arguments
      double d = atof(str[1]);
      double diffPR = atof(str[2]);
      int maxIt = atoi(str[3]);
      
      int j = 0, i = 0;
      int pageNum = List_num(pages);
      double urlPi[pageNum];// PR(,t)
      double PR[pageNum];// PR(,t+1)
      //initialise urlPi
      for (i = 0;i < pageNum;i++){
        urlPi[i] = (double)1/(double)pageNum;
      }
      // 1. Change ints -> doubles
      int iteration = 0;
      double diff = diffPR;//to enter the following loop
      List curr, curr2;
      //PR*W_in*W_out
      double PR_curr=0, W_IN=0, W_OUT=0;
      
      while(iteration < maxIt && diff >= diffPR){
          //PR[curr] to be calculate
          for(curr=pages,i=0; curr!=NULL; curr=curr->next,i++){
              double sum = 0;
              // check each curr2, and calculate PR*W_in*W_out
              for(curr2=pages,j=0; curr2!=NULL; curr2=curr2->next,j++){
                  if(isConnected(g,curr2->name,curr->name)){
                      PR_curr = (double)urlPi[j];
                      W_IN = W_in(g, curr2->name, curr->name);
                      W_OUT = W_out(g, curr2->name, curr->name);
                      
                      sum += PR_curr * W_IN * W_OUT;
                  }
              }
              PR[i] = (1-d)/pageNum + d*sum;
          }
          
          diff=0;
          for(i = 0; i < pageNum; i++) {
              diff += fabs(PR[i] - urlPi[i] );
          }
          
          for(i = 0; i < pageNum; i++) {
              urlPi[i] = PR[i];
          }  
              iteration++;
      }
      
      for (curr = pages, j = 0; curr != NULL; curr = curr->next){
        curr->rank = PR[j];
        j++;
      }

}
//
// reorder list by pagerank decending
// return a new list without changing the previous list
List order_PR(List URL){
    List new = NULL;
    List tmp = URL;
    while(tmp != NULL){
        new = insert_list_by_PR(new,tmp);
        tmp = tmp->next;
    }
    return new;
}

// insert list node by pagerank decending
List insert_list_by_PR(List pre_l, List new_node){
    List new = malloc(sizeof(ListNode));
    new->name = DUP(new_node->name);
    new->rank = new_node->rank;
    new->next = NULL;
    // if pre_l is empty
    if(pre_l == NULL)
        return new;
    //else check where to put new node
    List tmp = pre_l, prev = NULL;
    while(tmp!=NULL){
        if(new->rank > tmp->rank)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    // if new node should be put at the head of list
    if(prev == NULL){
        new->next = pre_l;
        return new;
    }
    // else just insert
    new->next = tmp;
    prev->next = new;
    return pre_l;
}




