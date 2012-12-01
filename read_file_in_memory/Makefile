CC=gcc

CFLAGS=-O2 -std=gnu89 -Wall -Wextra -Werror -Wstrict-prototypes -Wmissing-prototypes -Wcast-qual -Wcast-align -Wshadow -Winline -Wnested-externs -Wredundant-decls

SRC=src/read_file_in_memory.c
BIN_DIR=bin
BIN_FILE=read_file_in_memory

# .PHONY here for "bin" directory created. Otherwise command
# >make bin
# will give us such result:
# >make: `bin' is up to date.
.PHONY: bin

all: bin test

bin: $(SRC)
	@echo Creating "bin" directory
	mkdir -p bin
	
	@echo
	@echo Compiling...
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_FILE) $(SRC)

	@echo Done

clean:
	rm -rf $(BIN_DIR)

test:
	@echo
	@echo "*** Testing ***"
	@echo "Run $(BIN_DIR)/$(BIN_FILE)"
	$(BIN_DIR)/$(BIN_FILE)
