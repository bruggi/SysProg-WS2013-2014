/*
 * Scanner.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef SCANNER_HPP_INCLUDED
#define SCANNER_HPP_INCLUDED

#include "Automat.hpp"
#include "Buffer.h"

#include "ScannerError.hpp"
#include "Token.hpp"

#include <stdio.h>

class Scanner {

private:

	Automat* statemachine;
	char* characterBuffer;

	const size_t BUFSIZE = 256;

public:

	Scanner();
	~Scanner();

	ScannerError::type_t init();

	ScannerError::type_t getToken(Token& token_out);


}; // class Scanner



#endif /* SCANNER_HPP_ */
