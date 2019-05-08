#include "../include/cthread_lib.h"
#include <stdio.h>
#include <assert.h>

//Função ccreate, cria uma nova thread escalonando sua posição de acordo com sua priordade

int ccreate (void* (*start)(void*), void *arg, int prio) {
	if( !cthread_inicializado ) {

		// inicializa cthread
		cthread_init();
		
		// cria a thread para a main como solicitado
		cthread_create_main_thread();
	}
		

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

	cthread_priorty_thread(thread_info);

	return tid;
}


int cthread_priorty_thread(TCB_t* thread_info) {

	// move para fifo de prioridade correspondente
	int priority = thread_info->prio;
	AppendFila2(&cthread_priority_fifos[priority], (void*)thread_info);
	thread_info->state = CTHREAD_STATE_APTO;
	DEBUG_PRINT("Moved created thread %d (%p) to priority queue %d\n", thread_info->tid, thread_info, priority);

}

TCB_t* cthread_create_main_thread() {
	
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

int cthread_init() {
	 
	int i;
	// iniciliza filas de prioridade
	for(i = 0; i<CTHREAD_NUM_PRIORITY_LEVELS; i++) {
		DEBUG_PRINT("Creating fifo %d\n", i);
		CreateFila2(&cthread_priority_fifos[i]);
	}
	// inicializa fila de criação
	DEBUG_PRINT("Creating 'created' fifo.\n");
	CreateFila2(&cthread_created_fifo);
	// cria contexto de teminação
	DEBUG_PRINT("Creating termination context.\n");
	getcontext(&cthread_termination_context);
	cthread_termination_context.uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
	cthread_termination_context.uc_stack.ss_size = CTHREAD_STACK_SIZE;
	cthread_termination_context.uc_link = NULL;	
	makecontext(&cthread_termination_context, cthread_terminate, 0);
	
}

void cthread_terminate() {
	
	DEBUG_PRINT("Terminating thread %d\n", cthread_executing_thread->tid);
	// se algum thread esperando join, recoloca na fifo de aptors
	if( cthread_executing_thread->data != NULL ) {
		TCB_t* joined_thread = (TCB_t*)cthread_executing_thread->data;
		joined_thread->state = CTHREAD_STATE_APTO;
		AppendFila2(&cthread_priority_fifos[joined_thread->tid], (void*)joined_thread);
	}
	// libera memoria da stack
	assert(cthread_executing_thread->tid != 0);
	free((cthread_executing_thread->context).uc_stack.ss_sp);
	(cthread_executing_thread->context).uc_stack.ss_size = 0;
	// libera TCB
	free(cthread_executing_thread);
	cthread_executing_thread = NULL;
	// escalona proximo thread
	cthread_schedule(cthread_executing_thread, 0);


	DEBUG_PRINT("ERROR: THIS SHOULD NOT BE REACHED!!!!!\n");
	assert(0);


}
