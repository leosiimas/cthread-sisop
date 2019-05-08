#include "../include/cthread_lib.h"
#include <stdio.h>


// Função csem_init que faz a inicialização do semaforo

int csem_init(csem_t *sem, int count) {

    if (count > 0){		

		sem->fila = malloc(sizeof(FILA2));
		CreateFila2(sem->fila);
		sem->count = count;

		return 0;
	}

    return -1;
}
