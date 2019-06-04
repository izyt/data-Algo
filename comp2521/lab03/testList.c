// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
    char new[100]; 
    
	DLList myList3;//, mylist2, mylist1;
	FILE *fp3;//, *fp2, *fp1;
    //fp1 = fopen(argv[1],"r");
    //fp2 = fopen(argv[2],"r");
    fp3 = fopen(argv[3],"r");
    //myList1 = getDLList(fp1);
    //myList2 = getDLList(fp2);
    myList3 = getDLList(fp3);
    
    //test1 DLListBefore empty list
    printf("test1:\n");
    printf("WHOLE LIST:\n\n");
    putDLList(stdout,myList3);
    printf("\nfirst element: %s\n", myList3->first);
    printf("last element: %s\n", myList3->last);
    printf("current element: %s\n", myList3->curr);
    printf("number of elements %d\n\n", myList3->nitems);
    printf("operation: 'DLListBefore' 'Isabella' \n");
    printf("should contain one element now\n");
    new[100]="isabella";
	DLListBefore(lines,new);
	putDLList(stdout,myList);
	printf("NEW LIST:\n\n");
    putDLList(stdout,myList3);
    printf("\nfirst element: %s\n", myList3->first);
    printf("last element: %s\n", myList3->last);
    printf("current element: %s\n", myList3->curr);
    printf("number of elements %d\n\n", myList3->nitems);
	assert(validDLList(myList));
	fclose(fp1);
	//fclose(fp2);
	//fclose(fp3);
	return 0;
}





