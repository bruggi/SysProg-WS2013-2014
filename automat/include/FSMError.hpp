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
namespace FSMError {

typedef enum {

	OK = 0,
	NULL_POINTER = -1,
	UNEXPECTED_STATE = -2,
	INVALID_PARAM = -3

}type_t;

const char* const AsString(type_t result) {
	switch(result) {
	case OK:				return "OK"; break;
	case NULL_POINTER:		return "NULL_POINTER"; break;
	case UNEXPECTED_STATE:	return "FSM state undefined!"; break;
	case INVALID_PARAM:		return "Function parameter invalid"; break;

	default:				return "Undefined result type!"; break;
	} // end switch
	return "Error in AsString function!";
}

} // namespace FSMError

namespace FSMidentified {

typedef enum {
	INTEGER_ID = 1,
	IDENTIFIER_ID = 2,
	SPECIAL_SIGN_1_ID = 3,
	SPECIAL_SIGN_2_ID = 4,
	SIGN_ID = 5,
	COMMENT_END = 6,
	NOTHING
}type_t;

} // namespace FSMidentified

namespace FSMstatus {

typedef struct {
	uint8_t charsBack;
//WEITERMACHEN
	/*
	 * schritte zurück
	 * was identifiziert wurde
	 * error msg
	 *
	 */
}type_t;

} // namespace FSMstatus

} // namespace statemachine


#endif /* FSMERROR_HPP_INCLUDED */
