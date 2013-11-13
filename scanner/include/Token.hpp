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

class Token {

private:

	uint32_t row;
	uint32_t column;
	tokentype::type_t type;
	char* value;
	uint32_t valueSize;

	//TODO: Informations Container zu Token hinzufügen
	//InformationContainer* container;

public:

	Token();
	~Token();

	bool generate(const char* value, uint32_t valueSize,
					uint32_t row, uint32_t col,
					tokentype::type_t type);

	uint32_t getRow() const;
	uint32_t getColumn() const;
	tokentype::type_t getType() const;
	const char* const getValue(uint32_t& size) const;
	char* getValueRW(uint32_t& size);



}; // class Token


#endif /* TOKEN_HPP_INCLUDED */
