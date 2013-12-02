#
#	Makefile for creation of an static
#	automat.a library
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

OBJECTS = $(OBJ_DIR)/FSM.o $(OBJ_DIR)/StateMatrix.o

.PHONY : clean all

all: clean $(LIB_DIR)/libautomat.a

###
# compile automat
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "compile automat"
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) -c -fPIC -o $@  $<

###
# link shared library
#
$(LIB_DIR)/libautomat.a: $(OBJECTS)
	@echo "link automat"
	ar rcs $@ $^
	
###
# clean targets
#
clean:
	@echo "clean automat"
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_DIR)/*
	



