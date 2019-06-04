#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "scaledFootruleFunction.h"
#include "readData.h"

int main(int argc, char *argv[]){
    assert(argc>1);
    SFR(argc,argv);
    
    return 0;
}
