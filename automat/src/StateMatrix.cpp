/*
 * StateMatrix.cpp
 *
 *  Created on: 20.11.2013
 *      Author: typical
 */


/*
 * fehler bei ?y  und \nZ
 *
 */

#include "../include/StateMatrix.hpp"


namespace statemachine {

StateMatrix::StateMatrix() {
	initStateMatrix();
}

StateMatrix::~StateMatrix() {

}

void StateMatrix::initStateMatrix() {

	for(int row_chars = 0; row_chars < MAX_CHARACTERS; row_chars++) {
		for(int column_states = 0; column_states < _MAX_STATES_; column_states++) {

			/*	ASCII for digits	*/
			if(row_chars > 47 && row_chars < 58) {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::DIG_SEEN; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::DIG_SEEN; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end digits (if)

			/*	ASCII for letters	*/
			else if(row_chars > 64 && row_chars < 123) {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end letters (if)

			/*	all not important signs		*/
			else if((row_chars == '+') || (row_chars == '-') ||
					(row_chars == '<') || (row_chars == '>') ||
					(row_chars == '&') || (row_chars == ';') ||
					(row_chars == '(') || (row_chars == ')') ||
					(row_chars == '{') || (row_chars == '}') ||
					(row_chars == '[') || (row_chars == ']')    ){

				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end not important signs (if)

			else if(row_chars == '/') {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::COMMENT_1; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_END; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end '/' (if)

			else if(row_chars == '*') {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_3; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_3; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end '*' (if)

			else if(row_chars == '=') {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_1_SEEN; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SPCL_SGN_1_ID; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SPCL_SGN_2_ID; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::SGN_ID;		break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end '=' (if)

			else if(row_chars == '!') {
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_2_SEEN; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR;	break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				} // end switch
			} // end '!' (if)

			else { // all characters which are not listed above
				switch((states::type_states)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::START; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_1_ERR; break;
				case states::SGN_2_SEEN:	transitions[row_chars][column_states] = states::SGN_2_ERR; break;
				case states::SGN_2_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::COMMENT_1:		transitions[row_chars][column_states] = states::COMMENT_ERR; break;
				case states::COMMENT_2:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_3:		transitions[row_chars][column_states] = states::COMMENT_2; break;
				case states::COMMENT_ERR:	transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				case states::SGN_1_ERR:		transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				default:			transitions[row_chars][column_states] = states::TOTAL_ERR; break;
				}
			}
		} // end for states

	} // end for chars
}

/**
 * Returns the state code as an human readable string.
 * @param:	[in]state the given state to decode.
 * @return:	given state as string.
 */
const char* const StateMatrix::stateAsString(states::type_states state) {
	switch(state) {
	case states::START:			return "START";						break;
	case states::DIG_SEEN:		return "DIGIT_SEEN";				break;
	case states::INT_ID:		return "INTEGER_IDENTIFIED";		break;
	case states::LTR_SEEN:		return "LETTER_SEEN";				break;
	case states::ID_ID:			return "IDENTIFIER_IDENTIFIED";		break;
	case states::SGN_1_SEEN:	return "SIGN_1_SEEN";				break;
	case states::SGN_2_SEEN:	return "SIGN_2_SEEN";				break;
	case states::SPCL_SGN_1_ID:	return "SPECIAL_SIGN_1_SEEN";		break;
	case states::SPCL_SGN_2_ID:	return "SPECIAL_SIGN_2_SEEN";		break;
	case states::SGN_1_ERR:		return "Sign_1_ERROR";				break;
	case states::SGN_2_ERR:		return "SIGN_2_ERROR";				break;
	case states::SGN_ID:		return "SIGN_IDENTIFIED";			break;
	case states::COMMENT_1:		return "COMMENT_1";					break;
	case states::COMMENT_2:		return "COMMENT_2";					break;
	case states::COMMENT_3:		return "COMMENT_3";					break;
	case states::COMMENT_END:	return "COMMENT_END";				break;
	case states::COMMENT_ERR:	return "COMMENT_ERR";				break;
	case states::TOTAL_ERR:		return "TOTAL_ERR";					break;
	default:					return "!!State not defined!!";		break;
	} // end switch
	return "";
}


} // namespace statemachine
