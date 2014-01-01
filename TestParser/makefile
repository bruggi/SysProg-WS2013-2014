#
#	Makefile for testing the parser
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
LIB_DIR = ../shared_libs
BIN_DIR = Debug

AUTOMAT_DIR = ../automat
BUFFER_DIR = ../buffer
SYMTABLE_DIR = ../symtable    
SCANNER_DIR = ../scanner
PARSER_DIR = ../parser
 
INCLUDES = -I$(SCANNER_DIR)/include -I$(BUFFER_DIR)/src -I$(AUTOMAT_DIR)/include -I$(SYMTABLE_DIR) -I$(PARSER_DIR)/include
LIBS = -L$(LIB_DIR) -lscanner -lparser


OBJS = $(OBJ_DIR)/main.o
	
.PHONY : clean all

all: clean makeTestParser

makeTestParser: $(OBJS)
	g++ -g $^ $(LIBS) -o $(BIN_DIR)/TestParser
	
	
$(OBJ_DIR)/%.o :  $(SRC_DIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall $(INCLUDES) -o $@  $<

clean:
	@echo "clean TestParser"
	rm -rf $(OBJ_DIR)/*
