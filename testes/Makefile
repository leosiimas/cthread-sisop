#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib
CFLAGS=-lcthread -Wall -m32

all: testa_cyeld testa_join testa_setprio

testa_cyeld: testa_cyeld.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_cyeld testa_cyeld.c -L$(LIB_DIR) $(CFLAGS)

testa_join: testa_join.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_join testa_join.c -L$(LIB_DIR) $(CFLAGS)

testa_setprio: testa_setprio.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_setprio testa_setprio.c -L$(LIB_DIR) $(CFLAGS)
	
clean:
	rm -rf testa_cyeld testa_join testa_setprio
	
.PHONY: clean build-lib all