#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"



char *DUP(char* s);
char *SEP(char **str, const char *delims);
void freeList(List l);

char* DUP(char* s){
  int len = strlen(s);
  int i;
  char* copy = (char*)malloc(sizeof(char) * (len+1));
  for(i=0; i < len; i++){
    copy[i] = s[i];
  }
  copy[len] = '\0';
return copy;
}


char *SEP(char **str, const char *delims){

	char *token;
	if (*str == NULL) {
		/* No more tokens */
		return NULL;
	}
	token = *str;
	while (**str != '\0') {
		if (strchr(delims, **str)!=NULL) {
			**str = '\0';
			(*str)++;
			return token;
		}
		(*str)++;
	}
	/* There is no other token */
	*str = NULL;
	return token;
}


void freeList(List l){
    List curr = l;
    List temp;
    while(curr != NULL){
        temp = curr->next;
        free(curr->name);
        free(curr);
        curr = temp;
    }
    
}
