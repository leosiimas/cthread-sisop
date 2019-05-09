#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib
CFLAGS=-lcthread -Wall -m32

all: testa_basic testa_setprio testa_cjoin testa_semaforo testa_semaforo2 testa_semaforo3 testa_semaforo4

testa_setprio: testa_setprio.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_setprio testa_setprio.c -L$(LIB_DIR) $(CFLAGS)
	
testa_cjoin: testa_cjoin.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_cjoin testa_cjoin.c -L$(LIB_DIR) $(CFLAGS)

testa_basic: testa_basic.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_basic testa_basic.c -L$(LIB_DIR) $(CFLAGS)

testa_semaforo: testa_semaforo.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_semaforo testa_semaforo.c -L$(LIB_DIR) $(CFLAGS)

testa_semaforo2: testa_semaforo2.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_semaforo2 testa_semaforo2.c -L$(LIB_DIR) $(CFLAGS)

testa_semaforo3: testa_semaforo3.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_semaforo3 testa_semaforo3.c -L$(LIB_DIR) $(CFLAGS)

testa_semaforo4: testa_semaforo4.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_semaforo4 testa_semaforo4.c -L$(LIB_DIR) $(CFLAGS)
	
clean:
	rm -rf testa_cjoin testa_setprio testa_basic testa_semaforo testa_semaforo2 testa_semaforo3 testa_semaforo4
	
.PHONY: clean build-lib all