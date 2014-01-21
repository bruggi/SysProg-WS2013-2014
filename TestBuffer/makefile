C = g++
CFLAGS = -g -Wall -pthread 

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
 
INCLUDES = -I$(SCANNER_DIR)/include -I$(BUFFER_DIR)/src -I$(AUTOMAT_DIR)/include -I$(SYMTABLE_DIR)
LIBS = -L$(LIB_DIR) -lscanner


OBJS = $(OBJ_DIR)/main.o
	
.PHONY : clean all

all: clean makeTestBuffer

makeTestBuffer: $(OBJS)
	g++ -g -pthread $^ $(LIBS) -o $(BIN_DIR)/BufferTest
	
	
$(OBJ_DIR)/%.o :  $(SRC_DIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -pthread -Wall $(INCLUDES) -o $@  $<

clean:
	@echo "clean BufferTest"
	rm -rf $(OBJ_DIR)/*

