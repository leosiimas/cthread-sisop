/*
 *	
 *	Pequeno programa para testar a função csetprio
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void* func0(void *arg) {

    int  i = 1001, d0;

    while( 100 < i) {
        d0 = d0 + 1;
        if (d0 = 5)
        {
            printf("Eu sou a thread ID0 liberando \n");

            csetprio(3, 1);
            cyield();
            d0 = 0;
        }
    }
}

void* func1(void *arg) {

    int  i = 1001, d1;

    while( 100 < i) {
        d1 = d1 + 1;
        if (d1 = 5)
        {
            printf("Eu sou a thread ID1 liberando \n");
            cyield();
            d1 = 0;
        }
    }
}

void* func2(void *arg) {	

    int d2, i = 1001;

    while( 100 < i) {
        d2 = d2 + 1;
        if (d2 = 5)
        {
            printf("Eu sou a thread ID2 liberando \n");
            cyield();
            d2 = 0;
        }
    }
}

void* func3(void *arg) {

    int i = 1001, d3;

    while( 100 < i) {
        d3 = d3 + 1;
        if (d3 = 5)
        {
            printf("Eu sou a thread ID3 liberando \n");
            cyield();
            d3 = 0;
        }
    }
}

int main(int argc, char *argv[]) {

	int	id0, id1, id2, id3;
	int i;

    id3 = ccreate(func3, (void *)&i, 4);
	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&i, 2);
    id2 = ccreate(func2, (void *)&i, 3);

    cjoin(id3);
	cjoin(id0);
    cjoin(id1);
	cjoin(id2);
      
}

