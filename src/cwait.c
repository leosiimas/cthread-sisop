#include "../include/cthread_lib.h"
#include <stdio.h>


// Função cwait que faz a thread espera um recurso.

int cwait(csem_t *sem) {
    sem->count--;

	if(sem->count < 0) {

		AppendFila2(sem->fila, (void*)cthread_executing_thread);
		cthread_executing_thread->state = CTHREAD_STATE_BLOCK;		
		schedule(cthread_executing_thread, 1);
		
	}

    return 0;
}
