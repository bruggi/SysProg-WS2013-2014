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
	KEY_IF,					/*	'if'	*/
	KEY_WHILE,				/*	'while'	*/
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
	KEY_AMPERSAND			/*	'&'		*/

}type_t;

} // namespace tokentype


#endif /* TOKENTYPES_HPP_ */
