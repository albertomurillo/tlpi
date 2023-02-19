CC := gcc

BIN := bin
OBJ := obj

FLAGS := -O

LIB_LOG := $(OBJ)/log.o
LIB_ENV := $(OBJ)/env.o

.PHONY: build
build: $(BIN) $(OBJ) $(LIB_ENV) $(LIB_LOG)
	$(CC) $(FLAGS) fileio/bad_exclusive_open.c $(LIB_LOG) -o $(BIN)/bad_exclusive_open
	$(CC) $(FLAGS) fileio/copy.c $(LIB_LOG) -o $(BIN)/copy
	$(CC) $(FLAGS) fileio/seek_io.c $(LIB_LOG) -o $(BIN)/seek_io
	$(CC) $(FLAGS) fileio/t_readv.c $(LIB_LOG) -o $(BIN)/t_readv
	$(CC) $(FLAGS) memalloc/free_and_sbrk.c $(LIB_LOG) -o $(BIN)/free_and_sbrk
	$(CC) $(FLAGS) proc/display_env.c $(LIB_LOG) -o $(BIN)/display_env
	$(CC) $(FLAGS) proc/longjmp.c $(LIB_ENV) $(LIB_LOG) -o $(BIN)/longjmp
	$(CC) $(FLAGS) proc/modify_env.c $(LIB_ENV) $(LIB_LOG) -o $(BIN)/modify_env
	$(CC) $(FLAGS) proc/necho.c $(LIB_LOG) -o $(BIN)/necho
	$(CC) $(FLAGS) proc/setjmp_vars.c $(LIB_LOG) -o $(BIN)/setjmp_vars

$(LIB_ENV):
	$(CC) $(FLAGS) -c lib/env/env.c -o $(OBJ)/env.o

$(LIB_LOG):
	$(CC) $(FLAGS) -c lib/log/log.c -o $(OBJ)/log.o

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

run-linux-container:
	docker run -ti -v $(CURDIR):/workspace gcc:12
