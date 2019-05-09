#include "../include/cthread_lib.h"
#include <stdio.h>
#include <assert.h>

//Função ccreate, cria uma nova thread escalonando sua posição de acordo com sua priordade

int ccreate (void* (*start)(void*), void *arg, int prio) {

	if( !cthread_inicializado ) {

		// inicializa cthread
		cthread_init();
		
		// cria a thread para a main como solicitado
		create_main_thread();
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

// Coloca a thread criada na sua fila de prioridade
void cthread_priorty_thread(TCB_t* thread_info) {

	// move para fifo de prioridade correspondente
	int priority = thread_info->prio;
	AppendFila2(&cthread_priority_fifos[priority], (void*)thread_info);
	thread_info->state = CTHREAD_STATE_APTO;

}

// Inicia as filas de priordades thread
void cthread_init() {
	 
	int i;
	// iniciliza filas de prioridade
	for(i = 0; i<CTHREAD_NUM_PRIORITY_LEVELS; i++) {
		CreateFila2(&cthread_priority_fifos[i]);
	}

	// cria contexto de teminação
	getcontext(&cthread_termination_context);

	cthread_termination_context.uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
	cthread_termination_context.uc_stack.ss_size = CTHREAD_STACK_SIZE;
	cthread_termination_context.uc_link = NULL;	

	makecontext(&cthread_termination_context, cthread_terminate, 0);
	
}

// Ao terminar de executar uma thread, verifica se existe alguma outra esperando por ela.
void cthread_terminate() {
		
	// se algum thread esperando join, recoloca na fifo de aptos
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
	schedule(cthread_executing_thread, 0);
	assert(0);
}


