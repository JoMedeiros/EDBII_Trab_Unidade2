CC = g++
PROG = ABB
CPPFLAGS = -Wall -pedantic -ansi -std=c++14
RM = rm -rf
OBJS = bst.o

# Diretórios
LIB_DIR=./lib
INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc
TEST_DIR=./test

# Alvos
.PHONY: $(PROG) all dir run clean

all: dir $(PROG)

debug: CPPFLAGS += -g -O0
debug: $(PROG)

$(PROG): $(OBJ_DIR)/main.o $(OBJ_DIR)/ABB.o
	@echo "============="
	@echo "Linking target $@"
	$(CC) $(CPPFLAGS) -I$(INC_DIR) -o $(BIN_DIR)/$@ $^
	@echo "============="
	@echo "+++ [Executable file $(PROG) generated in $(BIN_DIR)] folder +++"
	@echo "============="

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

$(OBJ_DIR)/ABB.o: $(SRC_DIR)/ABB.cpp
	$(CC) -c $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

dir:
	mkdir -p bin build

run:
	$(BIN_DIR)/$(PROG)

clean: dir
	$(RM) $(BIN_DIR)/$(PROG)
	$(RM) $(OBJ_DIR)/*.o
