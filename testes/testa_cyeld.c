/*
 *	
 *	Pequeno programa para testar a função cyield
 *
 */

#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>


void* func0(void *arg) {


    
   int  i = 1001, d0;

    while( 100 < i) {
        d0 = d0 + 1;
        if (d0 = 5)
        {
            cyield();
            d0 = 0;
        }
    }

}

void* func1(void *arg) {

    printf("Eu sou a thread ID1 liberando \n");
    cyield();
    
}

int main(int argc, char *argv[]) {

	int	id0,id1;
	int i;

	id0 = ccreate(func0, (void *)&i, 0);	
    id1 = ccreate(func1, (void *)&i, 0);

    cjoin(id0);

}

