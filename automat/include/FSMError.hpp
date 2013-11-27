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
	IGNORE = -11,
	END_OF_FILE = -12,

	OK = 0,
	NULL_POINTER = -1,
	UNEXPECTED_STATE = -2,
	INVALID_PARAM = -3,
	UN_DEF = -100

}type_status;

typedef struct {
	uint8_t charsBack;
	type_status returnStatus;
	uint32_t currentRow;
	uint32_t currentColumn;
}status_struct;

const char* const asString(type_status status);

} // namespace FSMstatus

} // namespace statemachine


#endif /* FSMERROR_HPP_INCLUDED */
