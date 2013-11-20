/*
 * StateMatrix.hpp
 *
 *  Created on: 20.10.2013
 *      Author: typical
 */

#ifndef STATEMATRIX_HPP_INCLUDED
#define STATEMATRIX_HPP_INCLUDED

namespace statemachine {

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
}type_states;
}

class StateMatrix {

public:


/*	end states comes with an silent change back to START	*/
static const int _MAX_STATES_ = states::MAX_STATES - 7;// MAX_STATES - end states
static const int MAX_CHARACTERS  = 256;

void initStateMatrix();


/*			matrix[row][column]	*/
states::type_states transitions[MAX_CHARACTERS][_MAX_STATES_];

StateMatrix();
~StateMatrix();


const char* const stateAsString(states::type_states state);

}; // class statematrix

} // namespace statemachine

#endif /* STATEMATRIX_HPP_ */
