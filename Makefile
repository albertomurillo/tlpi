CC := gcc

BIN := bin
OBJ := obj

FLAGS := -O

LIBS := \
	$(OBJ)/env.o \
	$(OBJ)/getnum.o \
	$(OBJ)/log.o \
	$(OBJ)/ugid.o

UNAME := $(shell uname)

.PHONY: build
build: $(BIN) $(OBJ) $(LIBS)
	$(CC) $(FLAGS) $(LIBS) fileio/bad_exclusive_open.c -o $(BIN)/bad_exclusive_open
	$(CC) $(FLAGS) $(LIBS) fileio/copy.c -o $(BIN)/copy
	$(CC) $(FLAGS) $(LIBS) fileio/seek_io.c -o $(BIN)/seek_io
	$(CC) $(FLAGS) $(LIBS) fileio/t_readv.c -o $(BIN)/t_readv
	$(CC) $(FLAGS) $(LIBS) proc/display_env.c -o $(BIN)/display_env
	$(CC) $(FLAGS) $(LIBS) proc/longjmp.c -o $(BIN)/longjmp
	$(CC) $(FLAGS) $(LIBS) proc/modify_env.c -o $(BIN)/modify_env
	$(CC) $(FLAGS) $(LIBS) proc/necho.c -o $(BIN)/necho
	$(CC) $(FLAGS) $(LIBS) proc/setjmp_vars.c -o $(BIN)/setjmp_vars
	$(CC) $(FLAGS) $(LIBS) time/calendar_time.c -o $(BIN)/calendar_time
	$(CC) $(FLAGS) $(LIBS) time/current_time.c -o $(BIN)/current_time
	$(CC) $(FLAGS) $(LIBS) time/process_time.c -o $(BIN)/process_time
	$(CC) $(FLAGS) $(LIBS) time/show_time.c -o $(BIN)/show_time
	$(CC) $(FLAGS) $(LIBS) time/strtime.c -o $(BIN)/strtime
	$(CC) $(FLAGS) $(LIBS) syslim/t_fpathconf.c -o $(BIN)/t_fpathconf
	$(CC) $(FLAGS) $(LIBS) syslim/t_sysconf.c -o $(BIN)/t_sysconf
	$(CC) $(FLAGS) $(LIBS) sysinfo/procfs_pidmax.c -o $(BIN)/procfs_pidmax
	$(CC) $(FLAGS) $(LIBS) sysinfo/t_uname.c -o $(BIN)/t_uname

ifeq ($(UNAME), Linux)
	$(CC) $(FLAGS) $(LIBS) memalloc/free_and_sbrk.c -o $(BIN)/free_and_sbrk
	$(CC) $(FLAGS) $(LIBS) users_groups/check_password.c -o $(BIN)/check_password -lcrypt
	$(CC) $(FLAGS) $(LIBS) proccred/idshow.c -o $(BIN)/idshow
endif

$(OBJ)/env.o:
	$(CC) $(FLAGS) -c lib/env/env.c -o $(OBJ)/env.o

$(OBJ)/log.o:
	$(CC) $(FLAGS) -c lib/log/log.c -o $(OBJ)/log.o

$(OBJ)/getnum.o:
	$(CC) $(FLAGS) -c lib/getnum/getnum.c -o $(OBJ)/getnum.o

$(OBJ)/ugid.o:
	$(CC) $(FLAGS) -c lib/ugid/ugid.c -o $(OBJ)/ugid.o

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

run-linux-container:
	docker run -ti -v $(CURDIR):/workspace gcc:12
