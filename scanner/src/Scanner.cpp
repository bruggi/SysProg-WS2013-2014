/*
 * Scanner.cpp
 *
 *  Created on: 06.11.2013
 *      Author: typical
 */

#include "../include/Scanner.hpp"
#include <FSM.hpp>

Scanner::Scanner() {
	statemachine = NULL;
	characterBuffer = NULL;
	bufferClass = NULL;

}
Scanner::~Scanner() {
	if(characterBuffer != NULL) {
		delete characterBuffer;
	}
	if(bufferClass != NULL) {
		delete bufferClass;
	}
}

ScannerError::type_t Scanner::init(const char* path) {

	characterBuffer = (char*) malloc(BUFSIZE);
	if(characterBuffer == NULL) {
		return ScannerError::NULL_POINTER;
	}

	statemachine = new statemachine::FSM();
	bufferClass = new buffer::Buffer();

	/*	init buffer for use		*/
	buffer::bufferError::type_t result = bufferClass->initBuffer(path);
	if(result != buffer::bufferError::OK) {
		return ScannerError::BUFFER_INIT_ERR;
	}

	return ScannerError::OK;
}

ScannerError::type_t Scanner::getToken(Token& token_out) {

	if((bufferClass == NULL) || (statemachine == NULL)) {
		return ScannerError::SCANNER_NOT_INIT;
	}


	/*
	 *
	 * while(tempChar != '\0') {
	 * 		char tempChar = buffer.getchar();
	 *		statemachine.validate(tempChar);
	 *
	 *		// als if lieber switch-case
	 *		if(status_struct.status == INTEGER_ID) {
	 *			//create token
	 *			token(type::INT, characterBuffer, row, column, ...)
	 *			token_out = token;
	 *			return ScannerError::OK;
	 *		}
	 *		else if(status_struct.status == OK) {
	 *			qcharacterBuffer[index] = tempChar;
	 *		}
	 *
	 *		buffer.ungetchar(status_struct.charsBack);
	 */



	return ScannerError::OK;
}

