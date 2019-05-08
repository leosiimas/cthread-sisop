#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib
CFLAGS=-lcthread -Wall -m32

all: testa_cyeld testa_basic testa_setprio testa_cjoin

testa_cyeld: testa_cyeld.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_cyeld testa_cyeld.c -L$(LIB_DIR) $(CFLAGS)

testa_setprio: testa_setprio.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_setprio testa_setprio.c -L$(LIB_DIR) $(CFLAGS)
	
testa_cjoin: testa_cjoin.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_cjoin testa_cjoin.c -L$(LIB_DIR) $(CFLAGS)

testa_basic: testa_basic.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_basic testa_basic.c -L$(LIB_DIR) $(CFLAGS)
	
clean:
	rm -rf testa_cyeld testa_cjoin testa_setprio testa_basic
	
.PHONY: clean build-lib all