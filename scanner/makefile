#
#	Makefile for creation of an shared
#	scanner.so library
#
# author: johannes.kolb
#


CC = g++
CFLAGS = -g -Wall -pthread

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

INCLUDES = -I$(AUTOMAT_DIR)/include -I$(BUFFER_DIR)/src -I$(SYMTABLE_DIR)
#LIBS = -L$(AUTOMAT_DIR)/$(LIB_DIR) -L$(BUFFER_DIR)/$(LIB_DIR) -lautomat -lbuffer -lpthread

OBJECTS = $(OBJ_DIR)/Scanner.o \
$(OBJ_DIR)/Token.o \
$(AUTOMAT_DIR)/$(OBJ_DIR)/FSM.o \
$(AUTOMAT_DIR)/$(OBJ_DIR)/StateMatrix.o \
$(BUFFER_DIR)/$(OBJ_DIR)/Buffer.o \
$(BUFFER_DIR)/$(OBJ_DIR)/OutputBuffer.o \
$(SYMTABLE_DIR)/$(OBJ_DIR)/Symtable.o

.PHONY : clean all

all: automatLib bufferLib symtableLib clean scannerLib


automatLib:
	$(MAKE) -C $(AUTOMAT_DIR)

bufferLib:
	$(MAKE) -C $(BUFFER_DIR)

symtableLib:
	$(MAKE) -C $(SYMTABLE_DIR)

###
# compile 
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "compile scanner"
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) $(INCLUDES) -c -fPIC -o $@  $<

###
# link shared library
#
scannerLib: $(OBJECTS)
	@echo "link scanner"
	$(CC) -shared -o $(SHARED_LIB_DIR)/libscanner.so $^

# g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 

###
# clean targets
#
clean:
	@echo "clean scanner"
	rm -rf $(OBJ_DIR)/*
	rm -f $(SHARED_LIB_DIR)/scanner.so

	



