/*
 * StateMatrix.hpp
 *
 *  Created on: 20.10.2013
 *      Author: typical
 */

#ifndef STATEMATRIX_HPP_INCLUDED
#define STATEMATRIX_HPP_INCLUDED

namespace statemachine {
namespace statematrix {

namespace states {
typedef enum {
	START = 0,
	DIG_SEEN = 1,
	LTR_SEEN = 2,
	SGN_1_SEEN = 3,
	SGN_2_SEEN = 4,
	SGN_2_ERR = 5,
	COMMENT_1 = 6,
	COMMENT_2 = 7,
	COMMENT_3 = 8,
	COMMENT_ERR = 9,
	SGN_1_ERR = 10,
	TOTAL_ERR,	/*	end states	*/
	INT_ID,
	ID_ID,
	SPCL_SGN_1_ID,
	SPCL_SGN_2_ID,
	SGN_ID,
	COMMENT_END,
	MAX_STATES	/*	amount of states	*/
}type_t;

}// namespace states

/*	end states comes with an silent change back to START	*/
const int _MAX_STATES_ = states::MAX_STATES - 7;// MAX_STATES - end states

const int MAX_CHARACTERS  = 256;

/*			matrix[row][column]	*/
states::type_t transitions[MAX_CHARACTERS][_MAX_STATES_];

/**
 * Fills the transition table with the rule.
 */
void initStateMatrix() {

	for(int row_chars = 0; row_chars < MAX_CHARACTERS; row_chars++) {
		for(int column_states = 0; column_states < _MAX_STATES_; column_states++) {

			/*	ASCII for digits	*/
			if(row_chars > 47 && row_chars < 58) {
				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::DIG_SEEN; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::DIG_SEEN; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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
				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::LTR_SEEN; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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

				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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
				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::COMMENT_1; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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
				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::SGN_ID; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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
				switch((states::type_t)column_states) {
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
				switch((states::type_t)column_states) {
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

			else {
				switch((states::type_t)column_states) {
				case states::START:			transitions[row_chars][column_states] = states::START; break;
				case states::DIG_SEEN:		transitions[row_chars][column_states] = states::INT_ID; break;
				case states::LTR_SEEN:		transitions[row_chars][column_states] = states::ID_ID; break;
				case states::SGN_1_SEEN:	transitions[row_chars][column_states] = states::SGN_ID; break;
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
const char* const stateAsString(states::type_t state) {
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

} // namespace statematrix
} // namespace statemachine

#endif /* STATEMATRIX_HPP_ */
