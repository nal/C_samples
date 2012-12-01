CC=gcc

CFLAGS=-O2 -fPIC -Wall -Werror -Wextra -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wreturn-type -Wcast-qual -Wswitch -Wshadow -Wcast-align -Wno-unused-parameter -Wchar-subscripts -Winline -Wnested-externs -Wredundant-decls

CFLAGS_LIB=$(CFLAGS) -shared -Wl,-soname,$(LIB_SO) -o $(LIB_SO) $(OBJ_FILE)

SRC_DIR=src

OBJ_FILE=$(LIB_DIR)/libhello.o

LIB_DIR=lib
LIB_SOURCES=$(SRC_DIR)/libhello.c
LIB_SO=$(LIB_DIR)/libhello.so.1.0
LIB_SO_FILENAME=libhello.so.1.0

BIN_SOURCES=$(SRC_DIR)/use_libhello.c
BIN_DIR=bin
BIN=$(BIN_DIR)/use_libhello

all: obj lib bin info

obj: $(LIB_SOURCES)
	mkdir -p lib
	$(CC) $(CFLAGS) -c -o $(OBJ_FILE) $(LIB_SOURCES)

lib: $(OBJ_FILE)
	$(CC) $(CFLAGS_LIB)
	# Create symlink to allow linkage with -l hello
	ln -sf $(LIB_SO_FILENAME) $(LIB_DIR)/libhello.so

bin: $(BIN_SOURCES)
	mkdir -p bin
	$(CC) $(CFLAGS) -L $(LIB_DIR) -l hello -o $(BIN) $(BIN_SOURCES)

clean:
	rm -f $(LIB_DIR)/*.o $(LIB_DIR)/*.so $(LIB_DIR)/*.so.* t/use_libhello.out $(BIN)
	rm -rf bin lib t

test:
	@echo
	@echo "*** TESTING ***"
	@t/test.sh

info:
	@echo
	@echo "*** INFORMATION ***"
	@echo "To test result run these commands in shell:"
	@echo export LD_LIBRARY_PATH=\"./lib\"
	@echo ./bin/use_libhello
	@echo
	@echo Or run \"make test\"
