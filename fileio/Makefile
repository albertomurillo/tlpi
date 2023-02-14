CC = gcc
BIN_DIR = bin
BUILD_DIR = build

all: \
	bin \
	build \
	bad_exclusive_open \
	copy \
	seek_io

bad_exclusive_open: log.o
	$(CC) $@.c $(BUILD_DIR)/$^ -o $(BIN_DIR)/$@

copy: log.o
	$(CC) $@.c $(BUILD_DIR)/$^ -o $(BIN_DIR)/$@

seek_io: log.o
	$(CC) $@.c $(BUILD_DIR)/$^ -o $(BIN_DIR)/$@

log.o:
	$(CC) -c log.c -o $(BUILD_DIR)/log.o

bin:
	mkdir $(BIN_DIR)

build:
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)
