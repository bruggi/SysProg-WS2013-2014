/*
 * FSM.hpp
 *
 *  Created on: 19.10.2013
 *      Author: typical
 */

#ifndef FSM_HPP_INCLUDED
#define FSM_HPP_INCLUDED

#include "StateMatrix.hpp"
#include "FSMError.hpp"
#include <stdio.h>
#include <inttypes.h>


namespace statemachine {

class FSM  {

private:

	statematrix::states::type_t currentState;
	uint32_t row;
	uint32_t column;
	char currentChar;


	/*	normal states	*/
	int state_START();
	int state_DIG_SEEN();
	int state_LTR_SEEN();
	int state_SGN_1_SEEN();
	int state_SGN_2_SEEN();
	int state_SGN_2_ERR();
	int state_COMMENT_1();
	int state_COMMENT_2();
	int state_COMMENT_3();
	int state_COMMENT_ERR();

	/*	end states	*/
	int state_TOTAL_ERR();
	int state_INT_ID();
	int state_ID_ID();
	int state_SPCL_SGN_1_ID();
	int state_SPCL_SGN_2_ID();
	int state_SGN_ID();
	int state_COMMENT_END();

public:

	FSM();
	~FSM();

	FSMstatus::status_struct validateChar(const char inputChar);

	void printfTransTable();


}; // class FSM

} // namespace statemachine

#endif /* FSM_HPP_INCLUDED */
