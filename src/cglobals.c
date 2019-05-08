#include "../include/cthread_lib.h"


//Variaveis internas da cthread//

// indica se cthread foi inicializado
int cthread_inicializado = 0;

// filas de prioridade
FILA2 cthread_priority_fifos[CTHREAD_NUM_PRIORITY_LEVELS];

// fila de apto
FILA2 cthread_apto_fifo;

// thread em execução
TCB_t* cthread_executing_thread = NULL;

// main thread
TCB_t cthread_main_thread;

// id do proximo thread
int cthread_next_id = 1;

// contexto de terminação
ucontext_t cthread_termination_context;
