/*
 * Token.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

#include <inttypes.h>
#include <stdlib.h>
#include "Tokentypes.hpp"
#include "../../symtable/Pair.h"

typedef Pair<tokentype::type_t>* infoPtr_t;

class Token {

private:

	uint32_t row;
	uint32_t column;
	tokentype::type_t type;

	long value;
	infoPtr_t info;

	Token(const Token& tok);	// copy contructor should not be called!
	Token& operator=(const Token& tok);	// assign operator should not be called!


public:

	Token();
	~Token();

	bool generateINT(long value,	uint32_t row, uint32_t col);
	bool generateID(infoPtr_t info, uint32_t row, uint32_t column);
	bool generateSIGN(uint32_t row, uint32_t column, tokentype::type_t type);
	bool generateERROR(infoPtr_t info, uint32_t row, uint32_t column);

	uint32_t getRow() const;
	uint32_t getColumn() const;
	tokentype::type_t getType() const;
	long getValue() const;
	const infoPtr_t getInfo() const;
	infoPtr_t getInfo_rw() const;



}; // class Token


#endif /* TOKEN_HPP_INCLUDED */
