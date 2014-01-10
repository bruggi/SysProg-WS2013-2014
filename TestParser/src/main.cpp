/*
 * main.cpp
 *
 *  Created on: 01.01.2014
 *      Author: typical
 */


#include <Parser.hpp>

#include <stdio.h>


int main(int argc, char **argv) {


	if(argc < 4) {
		printf("Too less arguments given!\n");
		printf("\t:: ./TestParser <inputFile> <outputFile> <logFile>\n\n");
		return -1;
	}

	Parser* parser = new Parser();

	if(!parser->init(argv[1], argv[2], argv[3])) {
		printf("Parser init error!\n");
		return -1;
	}

	parserError::type_t result = parser->parse();
	if(result != parserError::OK) {
		printf("ParserError::%s(%d)\n", parserError::AsString(result), result);
		printf("see logFile: %s for more informations!\n", argv[3]);
		return 0;
	}

	if(parser->typeCheck()) {
		printf("typeCheck ok!\n");
		parser->makeCode();
	} else {
		printf("typeCheck not OK!\n");
		printf("see logFile: %s for more informations!\n", argv[3]);
		return 0;
	}

	printf("DONE!\n");
	return 0;
}





