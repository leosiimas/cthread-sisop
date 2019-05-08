#define DEBUG
#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* first_thread(void*);
void* second_thread(void*);
void* tirth_thread(void*);

int main() {

	int thread1 = ccreate(first_thread, (void*)1, 1);
	printf("Thread 1 created\n");

	cjoin(thread1);

	printf("I'm back!\n");
	return 0;
}


void* first_thread(void* arg) {
	
    int i;
    int thread2 = ccreate(second_thread, (void*)2, 1);
	printf("Thread 2 created\n");

    int thread3 = ccreate(tirth_thread, (void*)3, 0);
	printf("Thread 3 created\n");

    
    for( i = 0; i < 5; i++ ) { 

        if ( i < 1)
        {
            printf("mytrhead %d: hello world (%d)\n", (int)arg);		
            cjoin(thread2);
        }
        printf("mytrhead %d: hello world (%d)\n", (int)arg);
    }	
	
	return NULL;
}

void* second_thread(void* arg) {
	int i=0;

	for( i = 0; i < 5; i++ ) {
		printf("mytrhead %d: hello world 2 (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}

void* tirth_thread(void* arg) {
	int i=0;

	for( i = 0; i < 5; i++ ) {
		printf("mytrhead %d: hello world 3 (%d)\n", (int)arg, i+1);
	}

	return NULL;
}
