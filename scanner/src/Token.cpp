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
	case KEY_AMPERSAND:			return "Ampersand\t";
	case KEY_COMPARE:			return "Compare\t\t";
	case KEY_COMPARE_NOT:		return "Compare Not\t";
	case KEY_PRINT:				return "PRINT\t\t";
	case KEY_READ:				return "READ\t\t";
	case KEY_INT:				return "INT\t\t";
	case KEY_ELSE:				return "ELSE\t\t";
	default:					return "UNDEFINED\t";
	} // end switch
	return "UNDEFINED";
}
} // namesoace tokentype


Token::Token() {
	this->info = NULL;
}
Token::~Token() {

}

bool Token::generateINT(long value,	uint32_t row, uint32_t col) {

	this->value = value;
	this->row = row;
	this->column = col;
	this->type = tokentype::INTEGER;

	return true;
}
bool Token::generateID(infoPtr_t info, uint32_t row, uint32_t column) {

	if(info == NULL) {
		return false;
	}

	this->info = info;
	this->row = row;
	this->column = column;
	this->type = info->value;

	return true;
}
bool Token::generateSIGN(uint32_t row, uint32_t column, tokentype::type_t type) {

	this->row = row;
	this->column = column;
	this->type = type;
	this->info = NULL;

	return true;
}
bool Token::generateERROR(infoPtr_t info, uint32_t row, uint32_t column) {

	if(info == NULL) {
		return false;
	}

	this->row = row;
	this->column = column;
	this->info = info;
	this->type = tokentype::ERROR;

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

long Token::getValue() const {
	return this->value;
}
const infoPtr_t Token::getInfo() const {
	return this->info;
}
infoPtr_t Token::getInfo_rw() const {
	return this->info;
}
void Token::setType(tokentype::type_t t) {
	this->type = t;
}
