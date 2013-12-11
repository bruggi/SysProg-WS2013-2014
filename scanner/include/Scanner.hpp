/*
 * Scanner.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef SCANNER_HPP_INCLUDED
#define SCANNER_HPP_INCLUDED

#include <FSM.hpp>
#include <Buffer.h>
#include <Symtable.h>

#include "ScannerError.hpp"
#include "Token.hpp"

#include <stdio.h>

class Scanner {

private:

	buffer::Buffer* bufferClass;
	statemachine::FSM* statemachine;
	Symtable* symtable;
	char* characterBuffer;
	size_t bufIndexer;
	bool isOverflow;

	static const size_t BUFSIZE = 256;

	tokentype::type_t identifySign(char sign);
	ScannerError::type_t saveChar(char currentChar);

public:

	Scanner();
	~Scanner();

	ScannerError::type_t init(const char* path, Symtable* symtable);

	ScannerError::type_t getToken(Token& token_out);


}; // class Scanner



#endif /* SCANNER_HPP_ */
