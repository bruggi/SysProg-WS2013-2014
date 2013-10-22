/*
 * FSM.cpp
 *
 *  Created on: 19.10.2013
 *      Author: typical
 */

#include "../include/FSM.hpp"

namespace statemachine {

FSM::FSM() {
	statematrix::initStateMatrix();
	row = 0;
	column = 0;
	currentChar = 0;
	currentState = statematrix::states::START;
}

FSM::~FSM() {

}

FSMstatus::status_struct FSM::validateChar(const char inputChar) {

	FSMstatus::status_struct returnStruct;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;

	currentChar = inputChar;
	/*	get new state	*/
	currentState = statematrix::transitions[(uint8_t) currentChar][currentState];

	switch(currentState) {
	case statematrix::states::START:
	{
		// reachable?
	} break;
	case statematrix::states::DIG_SEEN:
	{

	} break;
	case statematrix::states::LTR_SEEN:
	{

	} break;
	case statematrix::states::SGN_1_SEEN:
	{

	} break;
	case statematrix::states::SGN_2_SEEN:
	{

	} break;
	case statematrix::states::SGN_2_ERR:
	{

	} break;
	case statematrix::states::COMMENT_1:
	{

	} break;
	case statematrix::states::COMMENT_2:
	{

	} break;
	case statematrix::states::COMMENT_3:
	{

	} break;
	case statematrix::states::COMMENT_ERR:
	{

	} break;
	case statematrix::states::TOTAL_ERR:
	{

	} break;
	case statematrix::states::INT_ID:
	{

	} break;
	case statematrix::states::ID_ID:
	{

	} break;
	case statematrix::states::SPCL_SGN_1_ID:
	{

	} break;
	case statematrix::states::SPCL_SGN_2_ID:
	{

	}break;
	case statematrix::states::SGN_ID:
	{

	} break;
	case statematrix::states::COMMENT_END:
	{

	}break;
	default:
	{

	} break;

	} // end switch for states


	return returnStruct;
}


/*	normal states	*/
int FSM::state_START() {

}
int FSM::state_DIG_SEEN() {

}
int FSM::state_LTR_SEEN() {

}
int FSM::state_SGN_1_SEEN() {

}
int FSM::state_SGN_2_SEEN() {

}
int FSM::state_SGN_2_ERR() {

}
int FSM::state_COMMENT_1() {

}
int FSM::state_COMMENT_2() {

}
int FSM::state_COMMENT_3() {

}
int FSM::state_COMMENT_ERR() {

}

/*	end states	*/
int FSM::state_TOTAL_ERR() {

}
int FSM::state_INT_ID() {

}
int FSM::state_ID_ID() {

}
int FSM::state_SPCL_SGN_1_ID() {

}
int FSM::state_SPCL_SGN_2_ID() {

}
int FSM::state_SGN_ID() {

}
int FSM::state_COMMENT_END() {

}


//------------------------------------------------------------------------------
/**
 * Prints the whole transition table out on stdout.
 */
void FSM::printfTransTable() {
	printf("ASCII\tSTART\tDIG_SEEN\tLTR_SEEN\tSNG_1_SEEN\tSGN_2_SEEN\tSGN_2_ERR\tCOMMENT_1\tCOMMENT_2\tCOMMENT_3\tCOMMENT_ERR\n\n");

	for(int row = 0; row < statematrix::MAX_CHARACTERS; row++) {
		printf("%d\t", row);

		for(int col = 0; col < statematrix::_MAX_STATES_; col++) {
			int printState = statematrix::transitions[row][col];
			printf("%s\t", statematrix::stateAsString((statematrix::states::type_t)printState));

		}
		printf("\n");
	}
}


} // namespace statemachine
