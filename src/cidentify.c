#include "../include/cthread_lib.h"
#include <string.h>

int cidentify (char *name, int size) {
	strncpy (name, "Gerente: Leonardo Abreu - 00243698\nMembro 2: Mateus Severgnini - 00206740\nmembro 3: Lucas Lauck - 00285688", size);
	return 0;
}
