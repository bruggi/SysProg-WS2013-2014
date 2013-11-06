/*
 * Scanner.cpp
 *
 *  Created on: 06.11.2013
 *      Author: typical
 */

#include "../include/Scanner.hpp"

Scanner::Scanner() {
	statemachine = NULL;
	characterBuffer = NULL;

}
Scanner::~Scanner() {
	if(characterBuffer != NULL) {
		delete characterBuffer;
	}
}

ScannerError::type_t Scanner::init() {

	characterBuffer = (char*) malloc(BUFSIZE);
	if(characterBuffer == NULL) {
		return ScannerError::NULL_POINTER;
	}

	statemachine = new Automat();


	return ScannerError::OK;
}

ScannerError::type_t Scanner::getToken(Token& token_out) {

}

