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

INCLUDES = -I
#LIBS = -L/usr/blub/lib -lblub
OBJECTS = $(OBJ_DIR)/FSM.o

.PHONY : clean

###
# compile automat
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) -c -o $@  $<

###
# link static library
#
$(LIB_DIR)/automat.a : $(OBJECTS)
	ar rcs $@ $^
	
###
# clean targets
#
clean:
	rm -rf Debug/*
	rm -rf lib/*
	



