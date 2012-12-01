CC=gcc

CFLAGS=-O2 -ansi -Wall

SRC=src/file_stat.c
BIN_DIR=bin
BIN_FILE=file_stat

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
	@echo "Get file size of bin/file_stat"
	./bin/file_stat
