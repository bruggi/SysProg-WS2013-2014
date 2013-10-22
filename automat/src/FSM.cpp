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
}

FSM::~FSM() {

}

FSMstatus::status_struct FSM::validateChar(const char inputChar) {

	FSMstatus::status_struct returnStruct;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;





	return returnStruct;
}





//------------------------------------------------------------------------------
/**
 * Prints the whole transition table out on stdout.
 */
void FSM::printfTransTable() {
	printf("BLUBBBBBBBB\n\n");
	printf("ASCII\tSTART\tDIG_SEEN\tLTR_SEEN\tSNG_1_SEEN\tSGN_2_SEEN\tSGN_2_ERR\tCOMMENT_1\tCOMMENT_2\tCOMMENT_3\tCOMMENT_ERR\n\n");

	for(int row = 0; row < statematrix::MAX_CHARACTERS; row++) {
		printf("%d\t", row);

		for(int col = 0; col < statematrix::_MAX_STATES_; col++) {
			int printState = statematrix::transitions[row][col];
			printf("%s\t", statematrix::stateAsString((statematrix::states)printState));

		}
		printf("\n");
	}
}


} // namespace statemachine
