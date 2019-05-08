#include "../include/cthread_lib.h"


// Função Cyield, executa a liberação voluntaria da CPU

int cyield() {
	// schedule
	return cthread_schedule(cthread_executing_thread, 0);
}
