/*
 * Token.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

#include <inttypes.h>
#include "Tokentypes.hpp"

class Token {

private:

	uint32_t row;
	uint32_t column;
	tokentype::type_t type;

public:

	Token();
	~Token();

	bool generate(const char* const name, uint32_t row, uint32_t col);

}; // class Token


#endif /* TOKEN_HPP_ */
