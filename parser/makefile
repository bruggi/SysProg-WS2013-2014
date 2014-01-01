#
#	Makefile for creation of an shared
#	parser.so library
#
# author: johannes.kolb
#

CC = g++

CFLAGS = -g -Wall

###
# path variables
#
SRC_DIR = src
OBJ_DIR = Debug
SHARED_LIB_DIR = ../shared_libs
LIB_DIR = lib
BIN_DIR = Debug

AUTOMAT_DIR = ../automat
BUFFER_DIR = ../buffer
SYMTABLE_DIR = ../symtable
SCANNER_DIR = ../scanner

INCLUDES = -I$(SCANNER_DIR)/include \
	-I$(BUFFER_DIR)/src \
	-I$(SYMTABLE_DIR) \
	-I$(AUTOMAT_DIR)/include


OBJECTS = $(OBJ_DIR)/ArrayNode.o \
$(OBJ_DIR)/DeclNode.o \
$(OBJ_DIR)/DeclsNode.o \
$(OBJ_DIR)/Exp2Node.o \
$(OBJ_DIR)/ExpNode.o \
$(OBJ_DIR)/IndexNode.o \
$(OBJ_DIR)/OpExpNode.o \
$(OBJ_DIR)/OpNode.o \
$(OBJ_DIR)/ParseTree.o \
$(OBJ_DIR)/ProgNode.o \
$(OBJ_DIR)/StatementNode.o \
$(OBJ_DIR)/StatementsNode.o \
$(OBJ_DIR)/Parser.o \
$(SCANNER_DIR)/$(OBJ_DIR)/Scanner.o \
$(SCANNER_DIR)/$(OBJ_DIR)/Token.o \
$(AUTOMAT_DIR)/$(OBJ_DIR)/FSM.o \
$(AUTOMAT_DIR)/$(OBJ_DIR)/StateMatrix.o \
$(BUFFER_DIR)/$(OBJ_DIR)/Buffer.o \
$(BUFFER_DIR)/$(OBJ_DIR)/OutputBuffer.o \
$(SYMTABLE_DIR)/$(OBJ_DIR)/Symtable.o

.PHONY : clean all

all:  clean parserLib


#scannerLib:
#	$(MAKE) -C $(SCANNER_DIR)

###
# compile 
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "compile parser"
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) $(INCLUDES) -c -fPIC -o $@  $<

###
# link shared library
#
parserLib: $(OBJECTS)
	@echo "link parser"
	$(CC) -shared -o $(SHARED_LIB_DIR)/libparser.so $^

# g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 

###
# clean targets
#
clean:
	@echo "clean parser"
	rm -rf $(OBJ_DIR)/*
	rm -f $(SHARED_LIB_DIR)/libparser.so

	




