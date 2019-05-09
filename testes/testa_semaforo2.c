#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread(void*);

int main() {

	int thread1;
	int thread2;
	int thread3;

	csem_init(&sem, 1);
	thread1 = ccreate(mythread, (void*)1, 2);
	thread2 = ccreate(mythread, (void*)2, 0);
	thread3 = ccreate(mythread, (void*)3, 2);

	cjoin(thread1);
	cjoin(thread2);
	cjoin(thread3);

	printf("Main: i'm back!\n");

	return 0;
}


void* mythread(void* arg) {
	int i=0;
	printf("Hello from thread %d\n", (int)(arg));

	cyield();

	for( i=0; i<3; i++ ) {
		cwait(&sem);
		printf("Thread %d inside critical sector\n", (int)(arg));
		cyield();
		printf("Thread %d lefting critical sector\n", (int)(arg));
		csignal(&sem);
	}
	printf("Thread %d ending\n", (int)(arg));

	return NULL;
}

