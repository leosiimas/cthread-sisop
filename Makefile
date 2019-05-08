#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
ifdef DEBUG
C_FLAGS=-Wall -m32 -DDEBUG
else
C_FLAGS=-Wall -m32
endif

OBJS=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

all: build_lib
	echo $(OBJS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(C_FLAGS)

   
build_lib: $(OBJS)
	mkdir -p $(LIB_DIR)
	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/*.o 

clean:
	rm -rf $(LIB_DIR)/*.a $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ .*~ *.sw?
	(find bin/ -type f -printf "$(BIN_DIR)/%P\n"; echo $(BIN_DIR)/support.o) | sort | uniq -u | xargs -r rm

.PHONY: clean build-lib all