#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "searchPagerankFunction.h"
#include "list.h"

#define MAX_LENGTH 1000

static List add_list(List L, char *url);

// find urls with 1 or more argv words
// return Link List of urls
List findMatchedUrls(char *argv[]){
    List l = NULL;
    
    //open "invertedIndex.txt"
    FILE *f = fopen("invertedIndex.txt","r");
    assert(f != NULL);
    //find matched argument words in file
    //read in each line of file
    char s[BUFSIZ], *word, *line;//line and word
    while(fgets(s,BUFSIZ, f)!=NULL){
        int i=0;
        //get rid of '\n'
        int length = strlen(s);
        s[length-1] = '\0';
        line = DUP(s);
        word = SEP(&line," ");
        
        //check if the start word in this line is the same as one argv
        while(argv[i]!=NULL){
            if(strcmp(argv[i],word)==0)
                break;
            i++;
        }
        
        // if match one of them
        // add each following url to SearchList
        if(argv[i]!=NULL){
            word = SEP(&line," ");
            while((word = SEP(&line," "))!=NULL){
                l = add_list(l, word);
            }
        }
    }
    fclose(f);
    
    return l;
}

//add pagerank into link list
void findPagerank(List urls){
    //open file
    FILE *f = fopen("pagerankList.txt","r");
    assert(f!=NULL);
    
    char word[MAX_LENGTH];
    //char garbage;
    int link;
    double PR;
    while(fscanf(f,"%s %d, %lf", word,&link,&PR)!=EOF){
        //get rid of ','
        int length = strlen(word);
        word[length-1] = '\0';
        
        //check if word matches one of the link list
        List tmp = urls;
        while(tmp!=NULL){
            if(strcmp(word,tmp->name)==0)
                tmp->rank = PR;
            tmp = tmp->next;
        }
        
    }
    fclose(f);
}

// add node to right place in List l
// by times and rank
static List Order_node(List l,List node){
    List new = malloc(sizeof(ListNode));
    new->name = node->name;//don't free node->name
    new->rank = node->rank;
    new->next = NULL;
    new->times = node->times;
    
    if(l == NULL)
        return new;
    
    List tmp = l, prev=NULL;
    while(tmp!=NULL){
        if(tmp->times < new->times || (tmp->times == new->times && tmp->rank < new->rank))
            break;
        prev = tmp;
        tmp=tmp->next;
    }
    //if new to be head
    if(prev==NULL){
        new->next = l;
        return new;
    }else{
        prev->next = new;
        new->next = tmp;
        return l;
    }
}

// make a new odered link list
// by times and rank
List Order_Match_PR(List urls){
    List tmp = urls, new = NULL, delete = NULL;
    while(tmp!=NULL){
        new = Order_node(new, tmp);
        delete = tmp;
        tmp=tmp->next;
        free(delete);
    }
    return new;
}



// don't care order just add to link list 
static List add_list(List L, char *url){
    //check if L is empty
    if(L==NULL){
        List new = malloc(sizeof(ListNode));
        new->name = DUP(url);
        new->rank = 0;
        new->next = NULL;
        new->times = 1;
        return new;
    }
    // check if it's already in the list
    List tmp = L, prev = NULL;
    while(tmp != NULL){
        if (strcmp(tmp->name,url)==0)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    
    // if already in
    if(tmp!=NULL){
        tmp->times++;
        return L;
    }
    // if not in
    else{
        // add new node
        List new = malloc(sizeof(ListNode));
        new->name = DUP(url);
        new->rank = 0;
        new->next = NULL;
        new->times = 1;
        assert(prev->next == NULL);
        prev->next = new;
        return L;
    }
}

