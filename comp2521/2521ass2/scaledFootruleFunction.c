#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include "scaledFootruleFunction.h"
#include "list.h"
#include "readData.h"

#define MAX_LENGTH 1000
#define MAX 1000000
//global v
int first[MAX]; 
int last[MAX]; 
int N=0;
double min=0;
int Argc=0;

void SFR(int argc, char *argv[]){
    Argc = argc;
    //read n file
    List L[argc];
    int i;
    for(i=1;i<argc;i++){
        L[i] = Read_file(argv[i]);
    }
    
    //make a link list of all urls, for later brute force
    List label = label_list(L);
    
    // number total num of url
    N = List_num(label);
    
    int best[N];
    min = N*argc;
    
    //recussion and find minimal W 
    recursion_bruteforce(0, best, label, L);
    
    //print min and best
    printf("%.7lf\n",min);
    
    char *print[N];
    List tmp = label;
    
    for(i=0;i<N;i++,tmp=tmp->next){
        print[best[i]-1]=tmp->name;
        
    }
    
    for(i=0;i<N;i++){
        printf("%s\n",print[i]);
    }
    
    //free
    for(i=1;i<argc;i++){
        freeList(L[i]);
    }

    return;
}

//read file and make a link list of urls
List Read_file(char *file_name){
    FILE *f = fopen(file_name,"r");
    
    assert(f!=NULL);
    char txt[MAX_LENGTH];
    List head = NULL, tail=NULL;
    int i=1;
    while(fscanf(f,"%s",txt)!=EOF){
        //add to link list
        List new = malloc(sizeof(ListNode));
        assert(new!=NULL);
        new->name = DUP(txt);
        new->times = i;
        new->next = NULL;
        //
        if(head == NULL){
            head = new;
            tail = new;
        }else{
            tail->next = new;
            tail = new;
        }
        i++;
    }
    fclose(f);
    
    return head;
}

//make a link list of all urls, for later brute force
List label_list(List *L){
    List new=NULL;
    int i;
    for(i=1;i<Argc;i++){
        List tmp = L[i];
        while(tmp!=NULL){
            new = add_to_label(new,tmp);
            tmp = tmp->next;
        }
        
    }
    return new;
}

// add each list node to link list
List add_to_label(List L, List n){
    
    if(L ==NULL){
        List new = malloc(sizeof(ListNode));
        new->name = DUP(n->name);
        new->times = 1;
        new->next = NULL;
        return new;
    }
    //check if n is in L
    List tmp = L, prev = NULL;
    int  time = 0;
    while(tmp!=NULL){
        if(strcmp(tmp->name,n->name)==0)return L;
        time = tmp->times;
        prev = tmp;
        tmp = tmp->next;
    }
    // n not in L
    List new = malloc(sizeof(ListNode));
    new->name = DUP(n->name);
    new->times = time+1;
    new->next = NULL;
    prev->next = new;
    
    return L;
}


void recursion_bruteforce(int step, int best[], List C, List T[]){
    int i;
    if(step == N)
        //calculate footrule
        foot_rule_min(best, C, T);
    else{
        for(i = 0; i < N; i++){
            if(!first[i]){
                first[i] = 1;
                last[step] = i + 1;
                recursion_bruteforce(step+1, best, C, T);
                first[i] = 0;
            }
        }
    }
}


// Calculate W and get compare with min
void foot_rule_min(int best[], List C, List T[]){

    double W=0, A, B;
    int  nC, nT, i=0, j=0;
    nC = List_num(C);
    
    List tmp = C;
    while(tmp!=NULL){
        //for each url in C
        // A = last[i]/n(C)
        A = (double)last[i]/(double)nC;
        //printf("A:%.7lf\n",A);
        for(j=0; j<Argc; j++){
            //for each T rank
            //B = url->times/nT
            nT = List_num(T[j]);
            List ttmmpp = T[j];
            while(ttmmpp!=NULL){
                if(strcmp(ttmmpp->name,tmp->name)==0)break;
                ttmmpp = ttmmpp->next;
            }
            // if find match
            if(ttmmpp != NULL){
                B = (double)ttmmpp->times/(double)nT;
                //printf("B:%.7lf\n",B);
                
                W = W + fabs(A-B);
            }
        }
        i++;
        tmp = tmp->next;
    }
    
    if(W <= min){
        int i=0;
        for(i=0;i<N;i++){
            best[i]=last[i];
        }
        min = W;
    }
    
    return;
}

