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
	NO_TYPE,
	INTEGER,
	ARRAY,
	INT_ARRAY,
	IDENTIFIER,
	ERROR,
	UNDEFINED,
	END_OF_FILE,
	KEY_IF,					/*	'if'	*/
	KEY_WHILE,				/*	'while'	*/
	KEY_READ,				/*	'read'	*/
	KEY_PRINT,				/*	'print'	*/
	KEY_ELSE,				/*	'else'	*/
	KEY_INT,				/*	'int'	*/
	KEY_PLUS,				/*	'+'		*/
	KEY_MINUS,				/*	'-'		*/
	KEY_SLASH,				/*	'/'		*/
	KEY_STAR,				/*	'*'		*/
	KEY_SEMICOLON,			/*	';'		*/
	KEY_BRAKET_RND_OPEN,	/*	'('		*/
	KEY_BRAKET_RND_CLOSE,	/*	')'		*/
	KEY_BRAKET_SQR_OPEN,	/*	'['		*/
	KEY_BRAKET_SQR_CLOSE,	/*	']'		*/
	KEY_BRAKET_CLY_OPEN,	/*	'{'		*/
	KEY_BRAKET_CLY_CLOSE,	/*	'}'		*/
	KEY_EQUAL,				/*	'='		*/
	KEY_BANG,				/*	'!'		*/
	KEY_BRAKET_ARRW_OPEN,	/*	'<'		*/
	KEY_BRAKET_ARRW_CLOSE,	/*	'>'		*/
	KEY_AMPERSAND,			/*	'&'		*/
	KEY_COMPARE,			/*	'=='	*/
	KEY_COMPARE_NOT			/*	'=!='	*/


}type_t;

const char* asString(type_t t);
} // namespace tokentype


#endif /* TOKENTYPES_HPP_ */
