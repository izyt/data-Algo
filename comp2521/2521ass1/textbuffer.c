#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "textbuffer.h"

#define MAX_CHAR_L 1024

typedef struct _TBNode {
	char   *string;
	struct _TBNode *next;
} TBNode;

typedef TBNode *Node;

typedef struct textbuffer{
    int nlines;
    TBNode *first;
    TBNode *last;
}Textbuffer;

//create newNode
//
static Node newNode (char *line){
    Node new;
	new = malloc(sizeof(TBNode));
	assert(new != NULL);
	
	new->string = strdup(line);
	new->next = NULL; 
    
    return new;
}

/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.
 */
TB newTB (char text[]) {
	//initialise TB
    
	TB L = malloc(sizeof(Textbuffer));
	assert (L != NULL);
	L->nlines = -1;//??
	L->first = L->last = NULL;
	
	char lines[MAX_CHAR_L];
	int i;
	for(i=0; text[i]!= '\0'; i++){
	    //find line stops
	    strcpy(lines,"");
	    int n = 0;
	    while(text[i]!='\n' && text[i]!='\0'){
	        lines[n]=text[i];
	        n++;
	        i++;
	    }
	    i++;
	    lines[n+1]='\n';
	    lines[n+2]='\0';
	    
	    //create new nodes and links
	    Node new;
	    new = newNode (lines);
	    if(L->first == NULL){
	        L->first = L->last = new;
	    }else{
	        L->last->next = new;
	        L->last = new;
	    }
	    L->nlines++;
	}
	return L;
}

//find nth node in tb
static Node nth_Node(TB tb, int n){
    if(n<0 || n > tb->nlines)
        return NULL;
    else{
        Node temp = tb->first;
        int i;
        for(i=0; i<n; i++)
            temp = temp->next;
        return temp;
    }
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
    Node temp = tb->first;
    Node delete = NULL;
    while(temp!= NULL){
        delete = temp;
        temp = temp->next;
        free(delete->string);
        free(delete);
        tb->nlines--;
    }
    free(tb);
}

static void n_to_a(int num, char *ch){
    //calculate num length
    int n = num, counter = 0;
    while(n >= 10){
        counter++;
        n = n/10;
    }
    //value put into string
    ch[counter+1] = '.';
    ch[counter+2] = ' ';
    ch[counter+3] = '\0';
    n = num;
    for (; counter >= 0; counter--){
        ch[counter] = n % 10 + '0';
        n = n/10;
    }
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number iff showLineNumbers == TRUE
 */
char *dumpTB (TB tb, int showLineNumbers){
	char *ch = malloc(sizeof (char)* MAX_CHAR_L);
	ch[0]='\0';
	// invalid line number
	if(showLineNumbers < tb-> nlines)
	    return ch;
	else{
	    //"number. " 
	    n_to_a(showLineNumbers, ch);
	    
	    //get nth line
	    int i;
	    Node temp = tb->first;
	    for(i=1; i < showLineNumbers && temp!= NULL; i++)
	        temp = temp->next;
	    // append
	    strcat(ch, temp->string);
	    
	    return ch;
	}
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
	return tb->nlines;
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
    // if invalid, abort
    if(pos2<pos1 || pos2 > tb->nlines || pos1<0)
        abort();
    else{
        Node temp = tb->first;
        int i;
        for(i=0; i< pos1; i++)
            temp = temp->next;
        // insert to the front
        for(i=pos1; i<= pos2; i++){
            char ch[MAX_CHAR_L];
            strcpy(ch, temp->string);
            strcpy(temp->string, prefix);
            strcat(temp->string, ch);
            temp = temp->next;
        }
    }
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
    // check valid
    if(pos > tb1->nlines) 
        abort();
    else{
        tb1->nlines = tb1->nlines + tb2->nlines +1;
        
        // if pos == 0
        if(pos == 0){
            Node temp = tb2->first;
            while(temp->next!= NULL)
                temp = temp->next;
            temp->next = tb1->first;
            tb1->first = tb2->first;
        }
        // pos!= 0
        else{
            //find pos-1 line in tb1
            int i;
            Node temp_0 = tb1->first;
            for(i=0; i < pos-1; i++)
                temp_0 = temp_0->next;
            //temp_0 = tb1 line pos-1
            Node temp_1 = temp_0->next;
            //temp_1 = tb1 line pos
            
            //link1
            temp_0->next = tb2->first;
            temp_0 = tb1->first;
            while(temp_0->next!=0)
                temp_0 = temp_0->next;
            //link2
            temp_0->next = temp_1;
        }
        //free tb2, but not nodes;
        free(tb2);
    }
}

//copy node list
static Node copy_list(TB tb){
    Node head = NULL;
    Node tail = NULL;
    Node tb_temp = tb->first;
    while(tb_temp!=NULL){
        Node new;
	    new = newNode (tb_temp->string);
        if(head == NULL){
            head = tail = new;
        }else{
            tail->next = new;
            tail = new;
        }
        tb_temp = tb_temp->next;
    }
    return head;
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
    // check valid
    if(pos > tb1->nlines) 
        abort();
    else{
        tb1->nlines = tb1->nlines + tb2->nlines +1;
        // cope tb2
        Node copy_tb2 = copy_list(tb2);
        //if pos == 0
        if(pos == 0){
            Node temp = copy_tb2;
            while(temp->next!= NULL)
                temp = temp->next;
            temp->next = tb1->first;
            tb1->first = copy_tb2;
        }
        // pos!= 0
        else{
            //find pos-1 line in tb1
            int i;
            Node temp_0 = tb1->first;
            for(i=0; i < pos-1; i++)
                temp_0 = temp_0->next;
            //temp_0 = tb1 line pos-1
            Node temp_1 = temp_0->next;
            //temp_1 = tb1 line pos
            
            //link1
            temp_0->next = copy_tb2;
            temp_0 = tb1->first;
            
            while(temp_0->next!=0)
                temp_0 = temp_0->next;
            //link2
            temp_0->next = temp_1;
        }
    }
}

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
TB cutTB (TB tb, int from, int to){
    // check valid
    if(to<from || to>tb->nlines || from<0)
        abort();
    else{
        Node temp_from = nth_Node(tb, from-1);
        Node temp_to = nth_Node(tb, to);
        // new tb for return
        TB new = malloc(sizeof (Textbuffer));
    	assert (new != NULL);
	    new->nlines = to - from;
    	new->first = temp_from->next;
        new->last = temp_to;
        // change link for tb
        temp_from->next = temp_to->next;
        // change link for new tb
        new->last->next = NULL;
        return new;
    }
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search){
	Match head_match = NULL, tail_match = NULL;
	
	int len_sea = strlen(search);
	Node temp;
	int line = 0;
	for(temp = tb->first; temp!=NULL; temp++){
	    int index;
	    int len_temp = strlen(temp->string);
	    for(index=0; index > len_temp-len_sea; index++){
	        //char first_ch = temp->string[i];
	        //if first character match
	        if(temp->string[index] == search[0]){
	            //check for other characters
	            int j=0;
	            int match = 1;
	            while(search[j]!='\0'){
	                if(search[j]!= temp->string[index + j]){
	                    match = 0;
	                    break;
	                }
	                j++;
	            }
	            //if all character match
	            if(match == 1){
	                //create new matchNode
	                Match new_match = malloc(sizeof(matchNode));
	                new_match->lineNumber = line;
	                new_match->charIndex = index;
	                
	                if(head_match == NULL){
	                    head_match = tail_match = new_match;
	                }else{
	                    tail_match->next = new_match;
	                    tail_match = new_match;
	                }
	            }
	        }
	    }
	    line++;
	}
	return head_match;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
    // check valid
    if(to<from || to > tb->nlines || from<0)
        abort();
    else{
        //from == 0
        if(from == 0){
            Node delete = NULL;
            Node temp = tb->first;
            int i;
            for(i=from; i < to+1; i++){
                delete = temp;
                temp = temp->next;
                free(delete->string);
                free(delete);
                tb->nlines--;
            }
            //if empty list
            if(tb->nlines == 0)
                tb->first = tb->last = NULL;
            else
                tb->first = temp;
        }
        
        //from > 0
        else{
            Node temp_0 = tb->first;
            int i;
            for(i=0; i<from-1; i++)
                temp_0 = temp_0->next;
            
            Node temp_1 = temp_0->next;//(from)
            Node delete = NULL;
            for(i=from; i<to+1; i++){
                delete = temp_1;
                temp_1 = temp_1->next;
                free(delete->string);
                free(delete);
                tb->nlines--;
            }
            //temp_0 is the last before from
            //temp_1 is the first after to
            
            //if last node been deleted
            if(temp_1==NULL){
                temp_0->next = NULL;
                tb->last = temp_0;
            }else
                temp_0->next = temp_1;
        }
    }
}

//rewrite for * and _ 
//
static void rewrite_Rich(Node temp, int i, int j){
    if(j == i+1)return;
    char new_s[MAX_CHAR_L];
    strcpy(new_s, temp->string);
    int a;
    for(a=0; new_s[a]!='\0'; a++){
        if(a<i)
            temp->string[a] = new_s[a];
        else if(a>i && a<j)
            temp->string[a+2] = new_s[a];
        else
            temp->string[a+5] = new_s[a];
    }
    temp->string[a+5] = '\0'; 
    temp->string[i] = '<';
    temp->string[i+2] = '>';
    temp->string[j+2] = '<';
    temp->string[j+3] = '/';
    temp->string[j+5] = '>';
    if(temp->string[i]=='*'){
        temp->string[i+1] = 'b';
        temp->string[j+4] = 'b';
        
    }else{
        temp->string[i+1] = 'i';
        temp->string[j+4] = 'i';
    }
}

/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
void formRichText (TB tb){
    Node temp;
    for(temp = tb->first; temp!=NULL; temp = temp->next){
        if(temp->string[0] == '#'){
            char new_s[MAX_CHAR_L];
            strcpy(new_s,temp->string);
            strcpy(temp->string, "<h1>");
            strcat(temp->string, new_s);
            strcat(temp->string, "</h1>");
        }else{
            int i;
            for(i=0; temp->string[i]!='\0'; i++){
                if(temp->string[i] == '*'){
                    //try find next *
                    int j;
                    for(j=i; temp->string[j]!='*' &&temp->string[j]!='\0'; j++){
                    }
                    //if find another *
                    if(temp->string[j] == '*'){
                        rewrite_Rich(temp, i, j);
                        i = j + 5;
                    }
                }
                else if(temp->string[i] == '_'){
                    //try find next _
                    int j;
                    for(j=i; temp->string[j]!='_' &&temp->string[j]!='\0'; j++){
                    }
                    //if find another _
                    if(temp->string[j] == '_'){
                        rewrite_Rich(temp, i, j);
                        i = j + 5;
                    }
                }
            }
        }
    }
}

/* Your whitebox tests
 */
void whiteBoxTests() {

}

