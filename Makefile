CC := gcc

BIN := bin
OBJ := obj

FLAGS := -O

LIBS := \
	$(OBJ)/env.o \
	$(OBJ)/getnum.o \
	$(OBJ)/log.o

.PHONY: build
build: $(BIN) $(OBJ) $(LIBS)
	$(CC) $(FLAGS) $(LIBS) fileio/bad_exclusive_open.c -o $(BIN)/bad_exclusive_open
	$(CC) $(FLAGS) $(LIBS) fileio/copy.c -o $(BIN)/copy
	$(CC) $(FLAGS) $(LIBS) fileio/seek_io.c -o $(BIN)/seek_io
	$(CC) $(FLAGS) $(LIBS) fileio/t_readv.c -o $(BIN)/t_readv
	$(CC) $(FLAGS) $(LIBS) memalloc/free_and_sbrk.c -o $(BIN)/free_and_sbrk
	$(CC) $(FLAGS) $(LIBS) proc/display_env.c -o $(BIN)/display_env
	$(CC) $(FLAGS) $(LIBS) proc/longjmp.c -o $(BIN)/longjmp
	$(CC) $(FLAGS) $(LIBS) proc/modify_env.c -o $(BIN)/modify_env
	$(CC) $(FLAGS) $(LIBS) proc/necho.c -o $(BIN)/necho
	$(CC) $(FLAGS) $(LIBS) proc/setjmp_vars.c -o $(BIN)/setjmp_vars

$(OBJ)/env.o:
	$(CC) $(FLAGS) -c lib/env/env.c -o $(OBJ)/env.o

$(OBJ)/log.o:
	$(CC) $(FLAGS) -c lib/log/log.c -o $(OBJ)/log.o

$(OBJ)/getnum.o:
	$(CC) $(FLAGS) -c lib/getnum/getnum.c -o $(OBJ)/getnum.o

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

run-linux-container:
	docker run -ti -v $(CURDIR):/workspace gcc:12
