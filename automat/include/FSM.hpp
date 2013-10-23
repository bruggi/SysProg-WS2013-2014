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
	FSMstatus::status_struct state_START();
	FSMstatus::status_struct state_DIG_SEEN();
	FSMstatus::status_struct state_LTR_SEEN();
	FSMstatus::status_struct state_SGN_1_SEEN();
	FSMstatus::status_struct state_SGN_2_SEEN();
	FSMstatus::status_struct state_SGN_2_ERR();
	FSMstatus::status_struct state_COMMENT_1();
	FSMstatus::status_struct state_COMMENT_2();
	FSMstatus::status_struct state_COMMENT_3();
	FSMstatus::status_struct state_COMMENT_ERR();

	/*	end states	*/
	FSMstatus::status_struct state_TOTAL_ERR();
	FSMstatus::status_struct state_INT_ID();
	FSMstatus::status_struct state_ID_ID();
	FSMstatus::status_struct state_SPCL_SGN_1_ID();
	FSMstatus::status_struct state_SPCL_SGN_2_ID();
	FSMstatus::status_struct state_SGN_ID();
	FSMstatus::status_struct state_COMMENT_END();

	bool charIsSign(const char inputChar);
public:

	FSM();
	~FSM();

	FSMstatus::status_struct validateChar(const char inputChar);

	void printfTransTable();


}; // class FSM

} // namespace statemachine

#endif /* FSM_HPP_INCLUDED */
