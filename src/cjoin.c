#include "../include/cthread_lib.h"
#include <stdio.h>


// Função cjoin, faz a sincronização das threads

int cjoin(int tid) {
	
	TCB_t* thread = cthread_find_thread(tid);
	if( thread == NULL ) {
		return -1;
	}

	cthread_executing_thread->state = CTHREAD_STATE_BLOCK;    
	cthread_schedule(cthread_executing_thread, 1);

	return 0;
}

TCB_t* cthread_find_thread(int tid) {
	// procura nas threads criadas
	TCB_t* next_thread = NULL;
	int found = 0;
	int i;
	FirstFila2(&cthread_created_fifo);
	while( !found && (next_thread = (TCB_t*)GetAtIteratorFila2(&cthread_created_fifo)) != NULL ) {
		found = next_thread->tid == tid;
		NextFila2(&cthread_created_fifo);
	}
	// procura threads aptos
	for( i=0; i<CTHREAD_NUM_PRIORITY_LEVELS; i++ ) {
		FirstFila2(&cthread_priority_fifos[i]);
		while( !found && (next_thread = (TCB_t*)GetAtIteratorFila2(&cthread_priority_fifos[i])) != NULL ) {
			found = next_thread->tid == tid;
			NextFila2(&cthread_priority_fifos[i]);
		}
	}

	if( !found ) {
		next_thread = NULL;
	}

	return next_thread;
}