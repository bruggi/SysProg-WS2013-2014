/*
 * main.cpp
 *
 *  Created on: 19.11.2013
 *      Author: typical
 */

#include <Scanner.hpp>
#include <Symtable.h>
#include <stdio.h>

#include <vector>

void printContent(Token* token);

int main (int argc, char** argv) {

	Scanner scanner;
	ScannerError::type_t result;
	Symtable* symtable = new Symtable();

	printf("Input: %s\n", argv[1]);

	result = scanner.init(argv[1], symtable);
	if(result != ScannerError::OK) {
		printf("Scanner init error <%d>!\n", result);
	}


	int counter = 0;	// for debug, stands for the amount of tokens
	do {
		if(counter == 480784) {
			counter++;
		}
		Token* currentToken = new Token();
		result = scanner.getToken(*currentToken);

		if(result == ScannerError::OK) {

			printf("Token<%d>\t", counter);
			printContent(currentToken);
		}



		counter++;
		delete currentToken;

	} while(result == ScannerError::OK);

	printf("\n\tENDE!!\n");

	return 0;
}


void printContent(Token* token) {

	tokentype::type_t type = token->getType();

	printf("%s\t", tokentype::asString(type));
	printf("Line: %u Column: %u\t", token->getRow(), token->getColumn());


	switch(type) {
	case tokentype::INTEGER:
	{
		printf("Value: %ld\n", token->getValue());
	} break;
	case tokentype::IDENTIFIER:
	{
		printf("Lexem: %s\n", token->getInfo()->key);
	} break;
	case tokentype::ERROR:
	{
		printf("Lexem: %s\n", token->getInfo()->key);
	} break;
	default:
	{
		printf("\n");
	} break;
	} // end switch

}

