#include "../include/cthread_lib.h"
#include <stdio.h>

// Função schedule, principal função que define qual thread estara em execucao e o que fazer com as que saem de execucao

int schedule(TCB_t* current_thread, int block) {
	
	
	int fifo_i=0;
	
	// coloca anterior na respectiva fila
	if( current_thread != NULL && !block) {
		current_thread->state = CTHREAD_STATE_APTO;
		AppendFila2(&cthread_priority_fifos[current_thread->prio], (void*)current_thread);
	}

	// obtém próximo thread
	TCB_t* next_thread = NULL;
	while( fifo_i < CTHREAD_NUM_PRIORITY_LEVELS && FirstFila2(&cthread_priority_fifos[fifo_i]) != 0 ) {
		fifo_i++;
	}
	if( fifo_i < CTHREAD_NUM_PRIORITY_LEVELS ) {
		next_thread = (TCB_t*)GetAtIteratorFila2(&cthread_priority_fifos[fifo_i]);
	}

	
	if( next_thread != NULL ) {

		// coloca como thread em execução
		cthread_executing_thread = next_thread;

		// remove novo da fila
		DeleteAtIteratorFila2(&(cthread_priority_fifos[fifo_i]));

		if( current_thread != NULL ) {

			// swap contexts
			current_thread->state = CTHREAD_STATE_EXEC;
			if( swapcontext( &(current_thread->context), &(next_thread->context) ) != 0 ) {
				return -1;
			}
		} else {

			// set context
			if( setcontext( &(next_thread->context) ) != 0 ) {
				return -1;
			}
		}

	} else {
		// continua current thread (não faz nada)
	}


	return 0;
}
