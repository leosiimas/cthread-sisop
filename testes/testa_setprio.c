/*
 *	
 *	Pequeno programa para testar a função csetprio
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void* func1(void*);
void* func2(void*);
void* func3(void*);

int main() {

	int thread1 = ccreate(func1, (void*)1, 0);
	printf("Thread 1 created\n");
	int thread2 = ccreate(func2, (void*)2, 1);
	printf("Thread 2 created\n");
    int thread3 = ccreate(func3, (void*)3, 1);
	printf("Thread 3 created\n");

	cjoin(thread1);
	cjoin(thread2);
    cjoin(thread3);

	printf("I'm back!\n");

	return 0;
}

void* func1(void* arg) {
	int i=0;

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}

void* func2(void* arg) {
	int i=0;

	//csetprio(0, 0);

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world 2 (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}


void* func3(void* arg) {
	int i=0;

	for( i=0; i<5; i++ ) {
        csetprio(0, 0);
		printf("mytrhead %d: hello world 3 (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}
