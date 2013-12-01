/*
 * Token.cpp
 *
 *  Created on: 09.11.2013
 *      Author: typical
 */

#include "../include/Token.hpp"
#include <string.h>


namespace tokentype {
const char* asString(type_t t) {
	switch(t) {
	case INTEGER:				return "Integer\t\t";
	case IDENTIFIER:			return "Identifier\t";
	case ERROR:					return "Error\t\t";
	case UNDEFINED:				return "UNDEFINED\t";
	case KEY_IF:				return "IF\t\t";
	case KEY_WHILE:				return "WHILE\t\t";
	case KEY_PLUS:				return "Plus\t\t";
	case KEY_MINUS:				return "Minus\t\t";
	case KEY_SLASH:				return "Slash\t\t";
	case KEY_STAR:				return "Star\t\t";
	case KEY_SEMICOLON:			return "Semicolon\t";
	case KEY_BRAKET_RND_OPEN:	return "Round bracket open";
	case KEY_BRAKET_RND_CLOSE:	return "Round bracket close";
	case KEY_BRAKET_SQR_OPEN:	return "Square bracket open";
	case KEY_BRAKET_SQR_CLOSE:	return "Square bracket close";
	case KEY_BRAKET_CLY_OPEN:	return "Clay bracket open";
	case KEY_BRAKET_CLY_CLOSE:	return "Clay bracket close";
	case KEY_EQUAL:				return "Assign\t\t";
	case KEY_BANG:				return "Not\t\t";
	case KEY_BRAKET_ARRW_OPEN:	return "Arrow bracket open";
	case KEY_BRAKET_ARRW_CLOSE:	return "Arrow bracket close";
	case KEY_AMPERSAND:			return "Ampersand\t\t";
	case KEY_COMPARE:			return "Compare\t\t";
	case KEY_COMPARE_NOT:		return "Compare Not\t";
	default:					return "UNDEFINED\t";
	} // end switch
	return "UNDEFINED";
}
} // namesoace tokentype


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

