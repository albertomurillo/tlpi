CC := gcc
CFLAGS := -O
LDFLAGS := -lcrypt

CLANGFORMAT := clang-format

SOURCEDIR := src
BINDIR := bin

LIB_DIR := $(SOURCEDIR)/lib
LIB := $(patsubst %.c,%.o,$(foreach dir,$(wildcard $(LIB_DIR)/*),$(wildcard $(dir)/*.c)))

CHAPTERS := $(filter-out $(LIB_DIR),$(wildcard $(SOURCEDIR)/*))
SOURCES := $(foreach dir, $(CHAPTERS),$(wildcard $(dir)/*.c))
TARGETS := $(patsubst $(SOURCEDIR)/%,$(BINDIR)/%,$(basename $(SOURCES)))

.PHONY: all format build clean

all: format build

format: $(SOURCES)
	@$(CLANGFORMAT) -i $(SOURCES)

build: $(LIB) $(TARGETS)

$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(BINDIR)/%: $(SOURCEDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LIB) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BINDIR) $(LIB)
