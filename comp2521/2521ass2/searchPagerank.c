#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "searchPagerankFunction.h"
#include "list.h"

int main(int argc, char* argv[]){
    // find urls with 1 or more argv words
    List urls = findMatchedUrls(argv);
    
    if(urls==NULL)return 0;
    
    // get pagerank from pagerankList.txt
    findPagerank(urls);
    
    urls = Order_Match_PR(urls);
    
    // output
    List tmp = urls;
    int i=0;
    while(tmp!=NULL && i<30){
        printf("%s\n",tmp->name);
        i++;
        tmp = tmp->next;
    }
    
    freeList(urls);
    
    
    return 0;
}
