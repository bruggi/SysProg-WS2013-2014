#
#	Makefile for creation of an shared
#	scanner.so library
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
LIB_DIR = lib
BIN_DIR = Debug

AUTOMAT_DIR = ../automat
BUFFER_DIR = ../buffer
#SYMTABLE_DIR = ../symtable

INCLUDES = -I$(AUTOMAT_DIR)/include -I$(BUFFER_DIR)/src
LIBS = -L$(AUTOMAT_DIR)/lib -L$(BUFFER_DIR)/lib -lautomat -lbuffer

OBJECTS = $(OBJ_DIR)/Scanner.o

.PHONY : clean all

all: automatLib bufferLib scannerLib


automatLib:
	$(MAKE) -C $(AUTOMAT_DIR)

bufferLib:
	$(MAKE) -C $(BUFFER_DIR)

#symtableLib:
#	$(MAKE) -C $(SYMTABLE_DIR)

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
	$(CC) -shared $(LIBS) -o $(LIB_DIR)/scanner.so $^

# g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 

###
# clean targets
#
clean:
	@echo "clean all"
	$(MAKE) -C $(AUTOMAT_DIR) clean
	$(MAKE) -C $(BUFFER_DIR) clean
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_DIR)/*

	



