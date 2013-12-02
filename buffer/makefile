#
#	Makefile for creation of an static
#	buffer.a library
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

OBJECTS = $(OBJ_DIR)/Buffer.o

.PHONY : clean all

all: clean $(LIB_DIR)/libbuffer.a

###
# compile buffer
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@echo "compile buffer"
	@echo "g++ $*.cpp"
	$(CC) $(CFLAGS) -c -fPIC -o $@  $<

###
# link shared library
#
$(LIB_DIR)/libbuffer.a: $(OBJECTS)
	@echo "link buffer"
	ar rcs $@ $^
	
###
# clean targets
#
clean:
	@echo "clean buffer"
	rm -rf Debug/*
	rm -rf $(LIB_DIR)/*
	



