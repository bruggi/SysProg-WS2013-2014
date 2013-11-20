/*
 * Token.cpp
 *
 *  Created on: 09.11.2013
 *      Author: typical
 */

#include "../include/Token.hpp"
#include <string.h>


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
const char* const Token::getValue(uint32_t& size) const {
	size = this->valueSize;
	return this->value;
}
char* Token::getValueRW(uint32_t& size) {
	size = this->valueSize;
	return this->value;
}

