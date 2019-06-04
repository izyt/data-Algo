#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "readData.h"

#define MAX_LENGTH 1000

//int FileIncludeWords(int n,char *word);
static int Tnum_url();
static List add_list(List L, char *url, double Idf);
void word_number(char *start, char *word, int *word_Tnum, int *word_num);

// find urls with 1 or more argv words
// and get summation of TfIdf value
List TfIdfMatchedUrls(char *argv[]){
    
    //invertedIndex.txt
    // counter total number of urls in collection.txt
    int url_Tnum = Tnum_url();
    
    // get a link list of all urls matched with argv
    // and calculate TfIdf
    List l = NULL;
    
    //open "invertedIndex.txt"
    FILE *f = fopen("invertedIndex.txt","r");
    assert(f != NULL);
    //find matched argument words in file
    //read in each line of file
    char s[BUFSIZ], *start, *word, *line;//line and word
    while(fgets(s,BUFSIZ, f)!=NULL){
        
        //get rid of '\n'
        int length = strlen(s);
        s[length-1] = '\0';
        line = DUP(s);
        start = SEP(&line," ");
        
        while(start[0]=='\0'){
            start = SEP(&line," ");
        }
        
        
        
        int i=0;
        //check if the start word in this line is the same as one argv
        while(argv[i]!=NULL){
            if(strcmp(argv[i],start)==0)
                break;
            i++;
        }
        
        // if match one of them
        if(argv[i]!=NULL){
            
            char *temp = DUP(line);
            char *temp1;
            
            int url_num = 0;          
            while((temp1 = SEP(&temp," "))!= NULL){
                if(temp1[0] == '\0')continue;
                url_num++;
            }
            assert(url_num);
            free(temp);
            free(temp1);
            double Idf = log10((double)url_Tnum/(double)url_num);
            
            // add each following url to SearchList
            //word = SEP(&line," ");
            while((word = SEP(&line," "))!=NULL){
                // total num of words in the file and 
                // and number of certain words in a file
                if(word[0] == '\0'){
                    continue;
                }
                
                int word_Tnum=0, word_num=0;
                word_number(start, word, &word_Tnum, &word_num);
                double Tf = (double)word_num/(double)word_Tnum;
                double TfIdf = Tf * Idf;
                // add to list
                l = add_list(l, word, TfIdf);
            }
        }
    }
    fclose(f);
    
    return l;
}


// total number of url
static int Tnum_url(){
    //open "collection.txt" to get total number of urls 
    FILE *f = fopen("collection.txt","r");
    assert(f!=NULL);
    char url[MAX_LENGTH];
    int counter = 0;
    while(fscanf(f,"%s",url)!=EOF)
        counter++;
    fclose(f);
    return counter;
}


// don't care order just add to link list 
static List add_list(List L, char *url, double TfIdf){
    
    //check if L is empty
    if(L==NULL){
        List new = malloc(sizeof(ListNode));
        new->name = DUP(url);
        new->rank = TfIdf;
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
        tmp->rank += TfIdf;
        return L;
    }
    // if not in
    else{
        // add new node
        List new = malloc(sizeof(ListNode));
        new->name = DUP(url);
        new->rank = TfIdf;
        new->next = NULL;
        new->times = 1;
        assert(prev->next == NULL);
        prev->next = new;
        return L;
    }
}


// count numbers of total words and certain word
void word_number(char *word, char *name, int *word_Tnum, int *word_num){
    char *url_name;
    url_name = DUP(name);
    strcat(url_name, ".txt");
    FILE *f = fopen(url_name,"r");
    assert(f!=NULL);
    free(url_name);
    // read <url>.txt file
    char txt[MAX_LENGTH];
    txt[0]='\0';
    while(fscanf(f,"%s",txt)!=EOF && strcmp(txt,"Section-2")!=0){}
    
    while(fscanf(f,"%s",txt)!=EOF && strcmp(txt,"#end")!=0){
        modify_words(txt);
        // count word_Tnum and word_num
        if (strcmp(txt,word)==0) (*word_num)++;
        (*word_Tnum)++;
    }
    
    fclose(f);
    
    
    return;
}



