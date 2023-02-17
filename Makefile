CC := gcc

BIN := bin
OBJ := obj

LIB_LOG := $(OBJ)/log.o
LIB_ENV := $(OBJ)/env.o

.PHONY: build
build: $(BIN) $(OBJ) $(LIB_ENV) $(LIB_LOG)
	$(CC) fileio/bad_exclusive_open.c $(LIB_LOG) -o $(BIN)/bad_exclusive_open
	$(CC) fileio/copy.c $(LIB_LOG) -o $(BIN)/copy
	$(CC) fileio/seek_io.c $(LIB_LOG) -o $(BIN)/seek_io
	$(CC) fileio/t_readv.c $(LIB_LOG) -o $(BIN)/t_readv
	$(CC) proc/necho.c $(LIB_LOG) -o $(BIN)/necho
	$(CC) proc/display_env.c $(LIB_LOG) -o $(BIN)/display_env
	$(CC) proc/modify_env.c $(LIB_ENV) $(LIB_LOG) -o $(BIN)/modify_env

$(LIB_ENV):
	$(CC) -c lib/env/env.c -o $(OBJ)/env.o

$(LIB_LOG):
	$(CC) -c lib/log/log.c -o $(OBJ)/log.o

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

run-linux-container:
	docker run -ti -v $(CURDIR):/workspace gcc:12
