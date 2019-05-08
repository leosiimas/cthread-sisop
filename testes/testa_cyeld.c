/*
 *	
 *	Pequeno programa para testar a função cyield
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
            cyield();
            d = 0;
        }
    }
}

void* func1(void *arg) {
	int i, d;
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

int main(int argc, char *argv[]) {

	int	id0, id1;
	int i;

	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&i, 0);

    cjoin(id0);
	cjoin(id1);
}

