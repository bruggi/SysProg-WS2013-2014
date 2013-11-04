/*
 * Tokentypes.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef TOKENTYPES_HPP_
#define TOKENTYPES_HPP_

namespace tokentype {

typedef enum {
	INTEGER,
	IDENTIFIER,
	ERROR,
	KEY_IF,
	KEY_WHILE,
	KEY_PLUS,
	KEY_MINUS,
	KEY_SLASH,
	KEY_STAR,
	KEY_

}type_t;

} // namespace tokentype


#endif /* TOKENTYPES_HPP_ */
