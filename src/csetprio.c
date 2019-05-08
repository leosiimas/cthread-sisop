#include "../include/cthread_lib.h"
#include <stdio.h>


// Função csetprio, altera a prioridade da thread

int csetprio(int tid, int prio) {

	cthread_executing_thread->prio = prio;

	if( cthread_check_priority(prio) ) {
		cthread_schedule(cthread_executing_thread, 0);
	}

	return 0;
}

int cthread_check_priority(int prio) {
	int i;
	for(i=prio-1; i>=0; i--) {
		if( FirstFila2(&cthread_priority_fifos[i]) == 0 ) {
			return 1;
		}
	}
	return 0;
}