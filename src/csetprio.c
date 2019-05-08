#include "../include/cthread_lib.h"
#include <stdio.h>


// Função csetprio, altera a prioridade da thread

int csetprio(int tid, int prio) {

	tid = NULL;

	if (prio < CTHREAD_NUM_PRIORITY_LEVELS ){
		cthread_executing_thread->prio = prio;
	}

	return 0;
}