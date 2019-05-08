/*
 *	
 *	Pequeno programa para testar a função csetprio
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void* func0(void *arg) {
    int i, d;
    while( 100 < i) {
        d = d + 1;
        if (d = 5)
        {
            printf("Eu sou a thread ID0 liberando \n");

            csetprio(3, 1);
            cyield();
            d = 0;
        }
    }
}

void* func1(void *arg) {	int i, d;

    while( 100 < i) {
        d = d + 1;
        if (d = 5)
        {
            printf("Eu sou a thread ID1 liberando \n");
            cyield();
            d = 0;
        }
    }
}

void* func2(void *arg) {	int i, d;

    while( 100 < i) {
        d = d + 1;
        if (d = 5)
        {
            printf("Eu sou a thread ID2 liberando \n");
            cyield();
            d = 0;
        }
    }
}

void* func3(void *arg) {	int i, d;

    while( 100 < i) {
        d = d + 1;
        if (d = 5)
        {
            printf("Eu sou a thread ID3 liberando \n");
            cyield();
            d = 0;
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

    cjoin(id0);
	cjoin(id1);
    cjoin(id2);
	cjoin(id3);
      
}

