
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include "BSTree.h"

#define MAX_LENGTH 1000
//free all malloc
//change Tree.c
//detach initialise Tree and List!!!!

// Create a set (list) of urls to process 
// by reading data from file "collection.txt"
List GetCollection(){
    FILE *f = fopen("collection.txt","r");
    assert(f!=NULL);
    char url[MAX_LENGTH];
    List head = NULL;
    
    while(fscanf(f,"%s",url)!=EOF){
        List new = malloc(sizeof(ListNode));
        new->name = DUP(url);
        new->rank = 0;
        new->next = NULL;
        
        //find where to put tmp
        if(head == NULL){
            head = new;
        }else{
            
            List tmp = head, prev=NULL;
            while(tmp!=NULL){
                if(strcmp(tmp->name,new->name)>0)
                    break;
                prev = tmp;
                tmp=tmp->next;
            }
            //if new to be head
            if(prev==NULL){
                new->next = head;
                head = new;
            }else{
                prev->next = new;
                new->next = tmp;
            }
        }
    }
    fclose(f);
    
    return head;
}

//return number of Lists in List linklist
int List_num(List url){
    int count = 0;
    List tmp = url;
    while(tmp!=NULL){
        tmp = tmp->next;
        count++;
    }
    return count;
}

// Create empty graph (use graph ADT in say graph.h and graph.c)
// For each url in the above list, read <url>.txt file
// and update graph by adding a node and outgoing links

Graph GetGraph(List url){
    
    // Create empty graph (use graph ADT in say graph.h and graph.c)
    int num_url = List_num(url);
    Graph G = newGraph(num_url);
    // For each url in the above list
    List tmp = url;
    while(tmp!=NULL){
        int counter = 0;
        char *url_name;
        url_name = DUP(tmp->name);
        strcat(url_name, ".txt");
        FILE *f = fopen(url_name,"r");
        // read <url>.txt file
        while(fscanf(f,"%s",url_name)!=EOF){
            if(strcmp(url_name,"#end")==0)break;
            if(counter >= 2){
                addEdge(G, tmp->name, url_name);
            }
            counter++;
        }
        fclose(f);
        tmp = tmp->next;
    }
    return G;
}

// all lower case
// no space
// no . , ; ?
void modify_words(char *word){
    int i=0;
    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z') word[i]=word[i]-'A'+'a';
        i++;
    }
    while(word[i-1]=='.' || word[i-1]==',' || word[i-1]==';' || word[i-1]=='?'){
        word[i-1] = '\0';
        i--;
    }
}


//url in pagerank order
// Create empty inverted list
// For each url in List_of_Urls
// read <url>.txt file, and update inverted index

BSTree GetInvertedList(List url){
    BSTree t=NULL;
    // Create empty inverted list

    // For each url in list
    List tmp = url;
    while(tmp!=NULL){
        // open file urlnum.txt
        char *url_name = DUP(tmp->name);
        strcat(url_name, ".txt");
        FILE *f = fopen(url_name,"r");
        assert(f != NULL);
        
        // read <url>.txt file
        char txt[MAX_LENGTH];
        txt[0]='\0';
        while(fscanf(f,"%s",txt)!=EOF && strcmp(txt,"Section-2")!=0){}
        
        while(fscanf(f,"%s",txt)!=EOF && strcmp(txt,"#end")!=0){
            modify_words(txt);
            //insert tree node
            t = BSTreeInsert(t, txt);
            //insert url
            urlInsert(t, txt, tmp->name);
        }
        
        fclose(f);
        tmp = tmp->next;
    }
    return t;
}


