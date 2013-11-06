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


INCLUDES = -I
#LIBS = -L/usr/blub/lib -lblub
OBJECTS = $(OBJ_DIR)/Scanner.o

.PHONY : clean

all: 


automatLib:
	$(MAKE) -C $(AUTOMAT_DIR)

bufferLib:
	$(MAKE) -C $(BUFFER_DIR)





###
# compile 
#
scannerLib: $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) -c -o $@  $<

###
# link shared library
#
$(LIB_DIR)/buffer.a : $(OBJECTS)
	ar rcs $@ $^
	
###
# clean targets
#
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_DIR)/*
	rm -rf $(AUTOMAT_DIR)/$(OBJ_DIR)/*
	rm -rf $(AUTOMAT_DIR)/$(LIB_DIR)/*
	rm -rf $(BUFFER_DIR)/$(OBJ_DIR)/*
	rm -rf $(BUFFER_DIR)/$(LIB_DIR)/*
	rm -rf $(SYMTABLE_DIR)/$(LIB_DIR)/*
	rm -rf $(SYMTABLE_DIR)/$(OBJ_DIR)/*
	



