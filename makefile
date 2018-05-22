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
.PHONY: $(PROG) all dir run clean doxy valgrindSimple valgrindFull lintComplete lint test

all: dir $(PROG)

debug: CPPFLAGS += -g -O0
debug: $(PROG)

$(PROG): $(OBJ_DIR)/main.o $(OBJ_DIR)/ABB.o $(OBJ_DIR)/Command.o
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

$(OBJ_DIR)/Command.o: $(SRC_DIR)/Command.cpp
	$(CC) -c $(CPPFLAGS) -I$(INC_DIR) -o $@ $<

dir:
	mkdir -p bin build doc

run:
	$(BIN_DIR)/$(PROG) -a data/valoresArvore.txt -i data/comandos.txt

clean: dir
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(DOC_DIR)/*

doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

valgrindSimple:
	valgrind -v --leak-check=full --show-reachable=yes $(BIN_DIR)/$(PROG)

valgrindFull:
	valgrind -v --leak-check=full --show-reachable=yes --track-origins=yes $(BIN_DIR)/$(PROG)

lintComplete:
	python2 cpplint.py --extensions=h, hpp, cpp, inl $(t)

lint:
	python2 cpplint.py --filter=-runtime/references,-whitespace/line_length --extensions=h, hpp, cpp, inl $(t)

test: CPPFLAGS += -g -O0
test: $(OBJ_DIR)/test.o $(OBJ_DIR)/ABB.o
	@echo "============="
	@echo "Linking target $@"
	$(CC) $(CPPFLAGS) -I$(INC_DIR) -o $(BIN_DIR)/$@ $^
	@echo "============="
	@echo "+++ [Executable file test generated in $(BIN_DIR)] folder +++"
	@echo "============="

$(OBJ_DIR)/test.o: $(SRC_DIR)/test.cpp
	$(CC) -c $(CPPFLAGS) -I$(INC_DIR) -o $@ $<