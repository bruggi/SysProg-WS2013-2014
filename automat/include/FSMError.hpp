/*
 * FSMError.hpp
 *
 *  Created on: 16.10.2013
 *      Author: typical
 *
 *    Header for error codes and handle codes for the FSM.
 */

#ifndef FSMERROR_HPP_INCLUDED
#define FSMERROR_HPP_INCLUDED

#include <inttypes.h>

namespace statemachine {

namespace FSMstatus {

typedef enum {
	INTEGER_ID = 1,
	IDENTIFIER_ID = 2,
	SPECIAL_SIGN_1_ID = 3,
	SPECIAL_SIGN_2_ID = 4,
	SIGN_ID = 5,
	COMMENT_END = 6,
	STEP_BACK = -10,
	COMMENT_START = -11,

	OK = 0,
	NULL_POINTER = -1,
	UNEXPECTED_STATE = -2,
	INVALID_PARAM = -3

}type_status;

typedef struct {
	uint8_t charsBack;
	type_status returnStatus;
	uint32_t currentRow;
	uint32_t currentColumn;
}status_struct;

const char* const asString(type_status status) {
	switch(status) {
	case INTEGER_ID:			return "Integer identified"; break;
	case IDENTIFIER_ID:		return "Identifier identified"; break;
	case SPECIAL_SIGN_1_ID:	return "Special sign 1 identified"; break;
	case SPECIAL_SIGN_2_ID:	return "Special sign 1 identified"; break;
	case SIGN_ID:				return "Sign identified"; break;
	case COMMENT_END:			return "Comment end"; break;
	case STEP_BACK:			return "Step back!"; break;
	case COMMENT_START:		return "Comment start"; break;
	case OK:					return "OK"; break;
	case NULL_POINTER:			return "NULL_POINTER"; break;
	case UNEXPECTED_STATE:		return "Unexpected state"; break;
	case INVALID_PARAM:		return "Invalid function param"; break;
	default:	return "Undefined!!"; break;
	} // end switch
	return "";
}

} // namespace FSMstatus

} // namespace statemachine


#endif /* FSMERROR_HPP_INCLUDED */
