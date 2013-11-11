/*
 * Token.cpp
 *
 *  Created on: 09.11.2013
 *      Author: typical
 */

#include "../include/Token.hpp"


Token::Token() {
	this->value = NULL;
}
Token::~Token() {
	if(this->value != NULL) {
		delete this->value;
	}
}

/**
 * Fills the Token with given params.
 *
 * @param [in] value		Pointer to the value of the token to fill.
 * @param [in] valueSize	Size of the value.
 * @param [in] row			Row of the token.
 * @param [in] col			Column of the token.
 * @param [in] type			The type of the token.
 *
 * @return		true		if token was successfully generated.
 * 				false		if pointers are NULL or if the token got
 * 							already an value.
 *
 */
bool Token::generate(const char* value, uint32_t valueSize, uint32_t row,
					 uint32_t col, tokentype::type_t type) {

	if((value == NULL) || (this->value != NULL)) {
		return false;
	}


	this->row = row;
	this->column = col;
	this->type = type;
	this->valueSize = valueSize;

	/*	generate memory block and save data into it		*/
	this->value = (char*) malloc(valueSize);
	if(this->value == NULL) {
		return false;
	}
	memcpy(this->value, value, valueSize);

	return true;
}

uint32_t Token::getRow() const {
	return this->row;
}
uint32_t Token::getColumn() const {
	return this->column;
}
tokentype::type_t Token::getType() const {
	return this->type;
}

/**
 * Gets the token value as string back.
 *
 * @param [out] outStr		Pointer to a memory block to write.
 * @param [in] outStrSize	Size if this pointer.
 *
 * @return		true		If string was successfully written.
 * 				false		If pointer was NULL, or size was too small.
 */
bool Token::getValueString(char* outStr, uint32_t outStrSize) {
	if((outStr == NULL) || (outStrSize < this->valueSize)) {
		return false;
	}
	memcpy(outStr, this->value, outStrSize);
	return true;
}

/**
 * Gets the token value as integer back.
 * Only works, if the token type is an "Integer"
 *
 * @param [out] outInt		Reference to an integer to write.
 *
 * @return		true		If value was successfully written.
 * 				false		If token is not an Integer.
 */
bool Token::getValueInteger(int& outInt) {
	if(this->type != tokentype::Integer) {
		return false;
	}
	outInt = (int) strol(this->value);
	return true;
}


