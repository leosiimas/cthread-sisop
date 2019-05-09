#include "../include/cthread_lib.h"
#include <stdio.h>

// Cria a thread da main com prioridade baixa
TCB_t* create_main_thread() {
	
	//obtém contexto da main

	// cria novo TCB
	
	cthread_main_thread.tid = 0;
	cthread_main_thread.state = CTHREAD_STATE_CREATION;
	cthread_main_thread.prio = CTHREAD_LOW_PRIORITY;
	getcontext(&(cthread_main_thread.context));

	cthread_executing_thread = &cthread_main_thread;
	cthread_inicializado = 1;
		
	return &cthread_main_thread;	
}
