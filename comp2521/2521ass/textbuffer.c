#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "textbuffer.h"

#define MAX_CHAR_L 10000

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
	    lines[n]='\n';
	    lines[n+1]='\0';
	    
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

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
    assert(tb!=NULL);
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
	if(!showLineNumbers){
	    Node temp;
	    for(temp=tb->first;temp!=NULL;temp=temp->next){
	        strcat(ch,temp->string);
	    }
	}else{
	    int i;
	    char *num = malloc(sizeof (char)*20);
	    Node temp = tb->first;
	    for(i=1; temp!= NULL; i++){
	        //"number. " 
	        n_to_a(i, num);
	        strcat(ch,num);
	        strcat(ch,temp->string);
	        temp = temp->next;
	    }

	}
	
	return ch;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
    
	return tb->nlines+1;
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
    assert(tb!=NULL);
    // if invalid, abort
    if(pos2<pos1 || pos2 > tb->nlines || pos1<0)
        abort();
    else{
        Node temp = tb->first;
        int i;
        for(i=0; i< pos1; i++)
            temp = temp->next;
        // insert to the front
        char *ch;
        for(i=pos1; i<= pos2 && temp!=NULL; temp = temp->next){
            ch=malloc(sizeof(char)*1000);
            ch[0]='\0';
            int j=0;
            while(prefix[j]!='\0'){
                ch[j]=prefix[j];
                j++;
            }
            int k=0;
            while(temp->string[k]!='\0'){
                ch[j]=temp->string[k];
                k++;
                j++;
            }
            ch[j]='\0';
            free(temp->string);
            temp->string = ch;
            i++;
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
    if(pos > tb1->nlines){
        tb1->nlines = tb1->nlines + tb2->nlines +1;
        tb1->last->next = tb2->first;
        tb1->last = tb2->last;
    }
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
            while(temp_0->next!=NULL && temp_0!=NULL)
                temp_0 = temp_0->next;
            //link2
            temp_0->next = temp_1;
        }
        //free tb2, but not nodes;
    }
    tb2->first = tb2->last = NULL;
    releaseTB(tb2);
    return;
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
    assert(tb1!=NULL && tb2!=NULL);
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
    assert(tb!=NULL);
    // check valid
    if(to<from || to>tb->nlines || from<0)
        abort();
    else{
        TB new = malloc(sizeof (Textbuffer));
        assert (new != NULL);
        //if from == 0
        if(from == 0){
            Node temp_to = tb->first; 
            int i;
            for(i=0; i < to; i++){// to
                temp_to = temp_to->next;
            }
	        new->nlines = to - from;
            //change links
            new->first = tb->first;
            new->last = temp_to;
            if(temp_to->next == NULL){
                tb->last = NULL;
                tb->first = NULL;
            }
            else{
                tb->first = temp_to->next;
            }
            new->last->next = NULL;
        }else{
            Node temp_from = tb->first; 
            int i;
            for(i=0; i < from-1; i++){//one node before from
                temp_from = temp_from->next;
            }
            Node temp_to = tb->first; 
            for(i=0; i < to; i++){// to
                temp_to = temp_to->next;
            }
            // new tb for return
	        new->nlines = to - from;
        	new->first = temp_from->next;
            new->last = temp_to;
            // change link for tb
            temp_from->next = temp_to->next;
            if(temp_to->next == NULL)
                tb->last = NULL;
            //change link for new tb
            new->last->next = NULL;
            
        }
        return new;
    }
}
//search match
static int search_compare(char *string, char *search, int j){
    int a = strlen(string);
    int b = strlen(search);
    if(j+b > a+1)return 0;
    int i;
    for(i=0; i<b; i++){
        if(string[i+j]!=search[i]){
            
            return 0;
        }
    }
    return 1;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search){
    Match temp = NULL; 
    Match tail = NULL;
    Node temp_node = tb->first;
    int line = 1;
    while(temp_node!= NULL){
        int j = 0;
        while (temp_node->string[j]!='\0'){
            if(search_compare(temp_node->string, search, j)==1){
                Match new = malloc(sizeof(matchNode));
                new->lineNumber = line;
                new->charIndex = j;
                new->next = NULL;
                if(temp == NULL){
                    temp = tail = new;
                }else{
                    tail->next = new;
                    tail = new;
                }
                
            }
            j++;
        }
        temp_node = temp_node->next;
        line++;
    }
    
    
    return temp;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
    assert(tb!=NULL);
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
static int rewrite_Rich(Node temp, int i, int j){
    if(j == i+1)return 0;
    char *new_s = malloc(sizeof(char)*MAX_CHAR_L);
    //strcpy(new_s, temp->string);
    int a;
    for(a=0; temp->string[a]!='\0'; a++){
        if(a<=i)
            new_s[a] = temp->string[a];
        else if(a>i && a<j)
            new_s[a+2] = temp->string[a];
        else
            new_s[a+5] = temp->string[a];
    }
    
    if(new_s[i]=='*'){
        new_s[i+1] = 'b';
        new_s[j+4] = 'b';
        
    }else{
        new_s[i+1] = 'i';
        new_s[j+4] = 'i';
    }
    new_s[a+5] = '\0'; 
    new_s[i] = '<';
    new_s[i+2] = '>';
    new_s[j+2] = '<';
    new_s[j+3] = '/';
    new_s[j+5] = '>';
    free(temp->string);
    temp->string = new_s;
    return 1;
    
}

/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
void formRichText (TB tb){
    assert(tb!=NULL);
    Node temp;
    for(temp = tb->first; temp!=NULL; temp = temp->next){
        if(temp->string[0] == '#'){
            char *new_s = malloc(sizeof(char)*MAX_CHAR_L);
            
            new_s[0]='<';
            new_s[1]='h';
            new_s[2]='1';
            new_s[3]='>';
            int i;
            for(i=1;temp->string[i]!='\n';i++){
                new_s[i+3]=temp->string[i];
            }
            new_s[i+3]='<';
            new_s[i+4]='/';
            new_s[i+5]='h';
            new_s[i+6]='1';
            new_s[i+7]='>';
            new_s[i+8]='\n';
            new_s[i+9]='\0';
            
            free(temp->string);
            temp->string = new_s;
        }
        else{
            int i;
            for(i=0; temp->string[i]!='\0'; i++){
                if(temp->string[i] == '*'){
                    //try find next *
                    int j;
                    for(j=i+1; temp->string[j]!='*' &&temp->string[j]!='\0'; j++){
                    }
                    //if find another *
                    if(temp->string[j] == '*'){
                        if(rewrite_Rich(temp, i, j)==1)i = j + 5;
                        
                    }
                }
                else if(temp->string[i] == '_'){
                    //try find next _
                    int j;
                    for(j=i+1; temp->string[j]!='_' &&temp->string[j]!='\0'; j++){
                    }
                    //if find another _
                    if(temp->string[j] == '_'){
                        if(rewrite_Rich(temp, i, j)==1)i = j + 5;
                        
                    }
                }
            }
        }
    }
}

/* Your whitebox tests
 */
void whiteBoxTests() {

    
    //test newTB
    char test[30]="abc\ndef\nxyz\n";
    TB One = newTB (test);
    assert (strcmp(One->first->string,"abc\n")==0);
    assert (One->nlines == 2);
    assert (strcmp(One->last->string,"xyz\n")==0);
    //test dampTB
    char *dump;
    dump = dumpTB (One, 2);
    assert(strcmp(dump,"1. abc\n2. def\n3. xyz\n")==0);
    //test linesTB
    int line = linesTB (One);
    assert(line == 3);
    //test addPrefixTB
    char prefix[10]="HI ";
    addPrefixTB(One, 0, 1, prefix);
    assert(strcmp(One->first->next->string,"HI def\n")==0);
    //releaseTB(One);
    //test merge
    char test1[30]="*3_*a\n#b\n";
    TB Two = newTB (test1);
    mergeTB(Two, 1, One);
    assert(strcmp(Two->first->next->string, "HI abc\n")==0);
    assert(strcmp(Two->last->string, "#b\n")==0);
    releaseTB(Two);
    // test merge special case
    Two = newTB (test1);
    One = newTB (test);
    mergeTB(Two, 0, One);
    assert(strcmp(Two->last->string, "#b\n")==0);
    assert(strcmp(Two->first->string, "abc\n")==0);
    releaseTB(Two);
    // test pastTB
    Two = newTB (test1);
    One = newTB (test);
    pasteTB (Two, 0, One);
    assert(strcmp(Two->last->string, "#b\n")==0);
    assert(strcmp(Two->first->string, "abc\n")==0);
    assert(strcmp(One->first->string, "abc\n")==0);
    releaseTB(Two);
    // test cutTB
    TB Three;
    Three = cutTB (One, 1, 1);
    assert(strcmp(Three->first->string, "def\n")==0);
    assert(strcmp(One->first->next->string, "xyz\n")==0);
    releaseTB(One);
    releaseTB(Three);
    // test cutTB special case
    One = newTB (test);
    Three = cutTB (One, 0, 1);
    assert(strcmp(Three->first->string, "abc\n")==0);
    assert(strcmp(One->first->string, "xyz\n")==0);
    releaseTB(One);
    releaseTB(Three);
    // test cutTB special case
    One = newTB (test);
    Three = cutTB (One, 0, 2);
    assert(strcmp(Three->last->string, "xyz\n")==0);
    assert(One->last == NULL);
    releaseTB(One);
    releaseTB(Three);
    //  test search
    char test2[30]="*3_*a\n#b\nabcdefghi\n";
    TB Four = newTB (test2);
    Match match1=NULL;
    char match_ch[30] = "_";
    match1 = searchTB(Four, match_ch);
    assert(match1->charIndex==2);
    releaseTB(Four);
    //test rich
    Two = newTB (test1);
    formRichText (Two);
    assert(strcmp(Two->first->string,"<b>3_</b>a\n")==0);
    assert(strcmp(Two->first->next->string,"<h1>b</h1>\n")==0);
}
