CC = gcc
BIN_DIR = bin
BUILD_DIR = build

all: \
	bin \
	build \
	bad_exclusive_open.c \
	copy.c \
	seek_io.c \
	t_readv.c

*.c: log.o
	$(CC) $@ $(BUILD_DIR)/$^ -o $(BIN_DIR)/$(basename $@)

log.o:
	$(CC) -c log.c -o $(BUILD_DIR)/log.o

bin:
	mkdir $(BIN_DIR)

build:
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)
