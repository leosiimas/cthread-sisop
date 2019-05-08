#include "../include/cthread_lib.h"
#include <stdio.h>

//Função ccreate, cria uma nova thread escalonando sua posição de acordo com sua priordade

int ccreate (void* (*start)(void*), void *arg, int prio) {
	
    // inicializa cthread
	cthread_init();

	// cria novo thread	
	TCB_t* thread_info = (TCB_t*) malloc(sizeof(TCB_t));
	int tid = thread_info->tid = cthread_next_id++;
	thread_info->state = CTHREAD_STATE_CREATION;
	thread_info->prio = prio;


	if( getcontext(&(thread_info->context)) != 0) {
		return -1;
	}

	(thread_info->context).uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
	(thread_info->context).uc_stack.ss_size = CTHREAD_STACK_SIZE;
	(thread_info->context).uc_link = &cthread_termination_context;

	makecontext(&(thread_info->context), (void*)(int)start, 1, (int*)arg);

	cthread_add_thread(thread_info);

	// cria a thread para a main como solicitado
	cthread_create_main_thread();

	// escalona thread se nova prioridade maior
	if( cthread_executing_thread == NULL || prio < cthread_executing_thread->prio ) {
		cthread_schedule(cthread_executing_thread, 0);
	}
	
	return tid;
}

TCB_t* cthread_create_main_thread() {
	if( !cthread_inicializado ) {
		///// obtém contexto da main
		// cria novo TCB
		
		cthread_main_thread.tid = 0;
		cthread_main_thread.state = CTHREAD_STATE_CREATION;
		cthread_main_thread.prio = CTHREAD_LOW_PRIORITY;
		//cthread_main_thread.data = NULL;
		getcontext(&(cthread_main_thread.context));
		cthread_executing_thread = &cthread_main_thread;
	
		cthread_inicializado = 1;
		 
		return &cthread_main_thread;
	}

	return NULL;
}

int cthread_add_thread(TCB_t* thread_info) {
	// coloca na fila de criados
	AppendFila2(&cthread_created_fifo, (void*) thread_info);
	return 0;
}