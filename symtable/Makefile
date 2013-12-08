#author bruggi

CC = g++
CFLAGS = -g -Wall

###
#Path variables
#
SRC_DIR = .
OBJ_DIR = Debug
LIB_DIR = lib
BIN_DIR = Debug

SCANNER_DIR = ../scanner
AUTOMAT_DIR = ../automat
BUFFER_DIR = ../buffer

OBJECTS = $(OBJ_DIR)/Symtable.o
INCLUDES = -I$(SCANNER_DIR)/include -I$(AUTOMAT_DIR)/include -I$(BUFFER_DIR)/src

.PHONY : clean all

all: clean $(LIB_DIR)/libsymtable.a

###
#Compile Symtable
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "compile Symtable"
	@echo "g++ $* .cpp"
	$(CC) $(CFLAGS) $(INCUDES) -c -fPIC -o $@ $<
	
###
#Link static library
#
$(LIB_DIR)/libsymtable.a: $(OBJECTS)
	@echo "link Symtable"
	ar rcs $@ $^
	
###
#Clean targets
#
clean:
	@echo " Clean Symtable"
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_DIR)/*

#all: main.cpp Hashtable.h List.h ListElement.h Pair.h Symtable.h
#	g++ main.cpp Symtable.cpp -g -I../scanner/include/ -o symtable
	 