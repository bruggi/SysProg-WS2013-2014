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

.PHONY : clean all

all: clean $(LIB_DIR)/libautomat.a

###
# compile automat
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "compile automat"
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) -c -o $@  $<

###
# link static library
#
$(LIB_DIR)/libautomat.a : $(OBJECTS)
	@echo "link automat"
	ar rcs $@ $^
	
###
# clean targets
#
clean:
	@echo "clean automat"
	rm -rf Debug/*
	rm -rf lib/*
	



