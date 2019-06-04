#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "textbuffer.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    whiteBoxTests();
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;

    // Cut first 3 lines of tb1
    tb2 = cutTB(tb1, 0, 2);
    s = dumpTB(tb1,FALSE);
    printf ("tb2 = cutTB(tb1, 0, 2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,FALSE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
    
    //
    char str2[] = "cut\n"
                  "#abc\n"
                  "*55*__\n";
    TB tb_1 = newTB(str2);
    printf("This is tb_1:\n%s\n",str2);              
    
    printf("addPrefix TB (tb_1,1,1,Hi):\n");
    char *s0;
    s0 = "Hi";
    addPrefixTB(tb_1,1,1,s0);
    char *s1;
    s1 = dumpTB(tb_1,0);
    assert(strcmp(s1,"cut\nHi#abc\n*55*__\n")==0);
    printf("tb_1:\n%s\n",s1);
    
    printf("formRichText(tb_1)\n");
    formRichText (tb_1);
    assert(strcmp(s1,"cut\nHiabc\n<b>55</b>__\n")==0);
    
    

    return EXIT_SUCCESS;
}
