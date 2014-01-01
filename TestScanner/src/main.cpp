/*
 * main.cpp
 *
 *  Created on: 19.11.2013
 *      Author: typical
 */

#include <Scanner.hpp>
#include <Symtable.h>
#include <OutputBuffer.hpp>
#include <stdio.h>

#include <vector>

void printContent(Token* token, buffer::OutputBuffer* outBuf);

int main (int argc, char** argv) {

	Scanner scanner;
	buffer::OutputBuffer* outBuffer = new buffer::OutputBuffer();
	ScannerError::type_t result;
	Symtable* symtable = new Symtable();

	if(argc < 4) {
		printf("Not enough arguments!\n");
		return 0;
	}

	printf("Input:  %s\n", argv[1]);
	printf("Output: %s\n", argv[2]);
	printf("Log:    %s\n", argv[3]);

	if(!outBuffer->init(argv[2], argv[3]) ){
		printf("OutputBuffer init error!\n");
		return 0;
	}

	outBuffer->printLog(buffer::logLevel::INFO, __func__, "starting scanner test!");
	result = scanner.init(argv[1], symtable);
	if(result != ScannerError::OK) {
		outBuffer->printLog(buffer::logLevel::FATAL, __func__, "Scanner init error <%d>!\n", result);
	}


	int counter = 0;	// for debug, stands for the amount of tokens
	do {
		if(counter == 480784) {
			counter++;
		}
		Token* currentToken = new Token();
		result = scanner.getToken(*currentToken);

		if(result == ScannerError::OK) {

			outBuffer->write("Token<%d>\t", counter);
			printContent(currentToken, outBuffer);
		}



		counter++;
		delete currentToken;

	} while(result == ScannerError::OK);

	outBuffer->printLog(buffer::logLevel::INFO, __func__, "ENDE!!");

	return 0;
}


void printContent(Token* token, buffer::OutputBuffer* outBuf) {

	tokentype::type_t type = token->getType();

	outBuf->write("%s\t", tokentype::asString(type));
	outBuf->write("Line: %u Column: %u\t", token->getRow(), token->getColumn());


	switch(type) {
	case tokentype::INTEGER:
	{
		outBuf->write("Value: %ld\n", token->getValue());
	} break;
	case tokentype::IDENTIFIER:
	{
		outBuf->write("Lexem: %s\n", token->getInfo()->key);
	} break;
	case tokentype::ERROR:
	{
		outBuf->write("Lexem: %s\n", token->getInfo()->key);
	} break;
	default:
	{
		outBuf->write("\n");
	} break;
	} // end switch

}

