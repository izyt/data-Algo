#include <stdio.h>
#include "searchTfIdfFunction.h"
#include "list.h"
#include "searchPagerankFunction.h"

int main(int argc, char* argv[]){
    // find urls with 1 or more argv words
    // and get summation of TfIdf value
    List urls = TfIdfMatchedUrls(argv);
    
    if(urls==NULL)return 0;
    
    urls = Order_Match_PR(urls);
    
    // output
    List tmp = urls;
    int i=0;
    while(tmp!=NULL && i<30){
        printf("%s  %.7lf\n",tmp->name,tmp->rank);
        i++;
        tmp = tmp->next;
    }
    freeList(urls);
    return 0;
}
