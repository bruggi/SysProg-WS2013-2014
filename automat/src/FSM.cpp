/*
 * FSM.cpp
 *
 *  Created on: 19.10.2013
 *      Author: typical
 */

#include "../include/FSM.hpp"

namespace statemachine {

namespace FSMstatus {

const char* const asString(type_status status) {
	switch(status) {
	case INTEGER_ID:			return "Integer identified"; break;
	case IDENTIFIER_ID:			return "Identifier identified"; break;
	case SPECIAL_SIGN_1_ID:		return "Special sign 1 identified"; break;
	case SPECIAL_SIGN_2_ID:		return "Special sign 1 identified"; break;
	case SIGN_ID:				return "Sign identified"; break;
	case COMMENT_END:			return "Comment end"; break;
	case STEP_BACK:				return "Step back!"; break;
	case IGNORE:				return "Ignore character"; break;
	case OK:					return "OK"; break;
	case END_OF_FILE:			return "End of File"; break;
	case NULL_POINTER:			return "NULL_POINTER"; break;
	case UNEXPECTED_STATE:		return "Unexpected state"; break;
	case INVALID_PARAM:			return "Invalid function param"; break;
	default:					return "Undefined!!"; break;
	} // end switch
	return "";
}

}//end namespace FSMstatus

//------------------------------------------------------------------------------
FSM::FSM() {
	statematrix = new StateMatrix();
	row = 0;
	column = 0;
	currentChar = 0;
	currentState = states::START;
}

FSM::~FSM() {

}

FSMstatus::status_struct FSM::validateChar(const char inputChar) {

	FSMstatus::status_struct returnStruct;

	currentChar = inputChar;
	/*	get new state	*/
	currentState = statematrix->transitions[(uint8_t) currentChar][currentState];


	switch(currentState) {
	case states::START:
	{
		returnStruct = state_START();
	} break;
	case states::DIG_SEEN:
	{
		returnStruct = state_DIG_SEEN();
	} break;
	case states::LTR_SEEN:
	{
		returnStruct = state_LTR_SEEN();
	} break;
	case states::SGN_1_SEEN:
	{
		returnStruct = state_SGN_1_SEEN();
	} break;
	case states::SGN_2_SEEN:
	{
		returnStruct = state_SGN_2_SEEN();
	} break;
	case states::SGN_1_ERR:
	{
		returnStruct = state_SGN_1_ERR();
	} break;
	case states::SGN_2_ERR:
	{
		returnStruct = state_SGN_2_ERR();
	} break;
	case states::COMMENT_1:
	{
		returnStruct = state_COMMENT_1();
	} break;
	case states::COMMENT_2:
	{
		returnStruct = state_COMMENT_2();
	} break;
	case states::COMMENT_3:
	{
		returnStruct = state_COMMENT_3();
	} break;
	case states::COMMENT_ERR:
	{
		returnStruct = state_COMMENT_ERR();
	} break;
	case states::TOTAL_ERR:
	{
		returnStruct = state_TOTAL_ERR();
		/*	empty transition	*/
		currentState = states::START;
	} break;
	case states::INT_ID:
	{
		returnStruct = state_INT_ID();
		/*	empty transition	*/
		currentState = states::START;
	} break;
	case states::ID_ID:
	{
		returnStruct = state_ID_ID();
		/*	empty transition	*/
		currentState = states::START;
	} break;
	case states::SPCL_SGN_1_ID:
	{
		returnStruct = state_SPCL_SGN_1_ID();
		/*	empty transition	*/
		currentState = states::START;
	} break;
	case states::SPCL_SGN_2_ID:
	{
		returnStruct = state_SPCL_SGN_2_ID();
		/*	empty transition	*/
		currentState = states::START;
	}break;
	case states::SGN_ID:
	{
		returnStruct = state_SGN_ID();
		/*	empty transition	*/
		currentState = states::START;
	} break;
	case states::COMMENT_END:
	{
		returnStruct = state_COMMENT_END();
		/*	empty transition	*/
		currentState = states::START;
	}break;
	default:
	{
		returnStruct = state_TOTAL_ERR();
		/*	empty transition	*/
		currentState = states::START;
	} break;

	} // end switch for states

	/*	collect row and column counters	*/
	returnStruct.currentColumn = column;
	returnStruct.currentRow = row;

	return returnStruct;
}


/*	normal states	*/
FSMstatus::status_struct FSM::state_START() {
	FSMstatus::status_struct returnStruct;
	if(currentChar == '\n') {row++; column = 0;}
	else {column++;}
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;

	if(currentChar == '\0') {
		returnStruct.returnStatus = FSMstatus::END_OF_FILE;
	}
	else if(currentChar == ' ') {
		returnStruct.returnStatus = FSMstatus::IGNORE;
	}

	return returnStruct;
}

FSMstatus::status_struct FSM::state_DIG_SEEN() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_LTR_SEEN() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SGN_1_SEEN() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SGN_2_SEEN() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::OK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SGN_1_ERR() {
	FSMstatus::status_struct returnStruct;
	column -= 1;	/*	currentChar doesn't counts in column count here	*/
	returnStruct.charsBack = 2;
	returnStruct.returnStatus = FSMstatus::STEP_BACK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SGN_2_ERR() {
	/*	ungetchar(3)	*/
	FSMstatus::status_struct returnStruct;
	column -= 2;	/*	currentChar don't counts in col counter here	*/
	returnStruct.charsBack = 3;
	returnStruct.returnStatus = FSMstatus::STEP_BACK;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_COMMENT_1() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::IGNORE;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_COMMENT_2() {
	FSMstatus::status_struct returnStruct;
	if(currentChar == '\n') {row++; column = 0;}
	else {column++;}
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::IGNORE;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_COMMENT_3() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::IGNORE;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_COMMENT_ERR() {
	FSMstatus::status_struct returnStruct;
	/*	ungetchar(2)	*/
	column -= 1;	/*	currentChar don't counts in col counter here	*/
	returnStruct.charsBack = 2;
	returnStruct.returnStatus = FSMstatus::STEP_BACK;
	return returnStruct;
}

/*	end states	*/
FSMstatus::status_struct FSM::state_TOTAL_ERR() {
	FSMstatus::status_struct returnStruct;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::UNEXPECTED_STATE;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_INT_ID() {
	FSMstatus::status_struct returnStruct;
	/*	'else' wount be counted	*/
	returnStruct.charsBack = 1;
	returnStruct.returnStatus = FSMstatus::INTEGER_ID;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_ID_ID() {
	FSMstatus::status_struct returnStruct;
	/*	'else' wount be counted	*/
	returnStruct.charsBack = 1;
	returnStruct.returnStatus = FSMstatus::IDENTIFIER_ID;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SPCL_SGN_1_ID() {
	FSMstatus::status_struct returnStruct;
	/*	'=' counts	*/
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::SPECIAL_SIGN_1_ID;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SPCL_SGN_2_ID() {
	FSMstatus::status_struct returnStruct;
	/*	'=' counts	*/
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::SPECIAL_SIGN_2_ID;
	return returnStruct;
}

FSMstatus::status_struct FSM::state_SGN_ID() {
	FSMstatus::status_struct returnStruct;
	/*	is the current character a sign what interests me?	*/
	if(charIsSign(currentChar)) {
		column++;
		returnStruct.charsBack = 0;
		returnStruct.returnStatus = FSMstatus::SIGN_ID;
	} else {
		/*	no interesting sign found	*/
		returnStruct.charsBack = 1;
		returnStruct.returnStatus = FSMstatus::STEP_BACK;
	}

	return returnStruct;
}

FSMstatus::status_struct FSM::state_COMMENT_END() {
	FSMstatus::status_struct returnStruct;
	column++;
	returnStruct.charsBack = 0;
	returnStruct.returnStatus = FSMstatus::COMMENT_END;
	return returnStruct;
}


bool FSM::charIsSign(const char inputChar) {
	if((inputChar == '+') || (inputChar == '-') ||
		(inputChar == '<') || (inputChar == '>') ||
		(inputChar == '&') || (inputChar == ';') ||
		(inputChar == '(') || (inputChar == ')') ||
		(inputChar == '{') || (inputChar == '}') ||
		(inputChar == '[') || (inputChar == ']') ||
		(inputChar == '/') || (inputChar == '*') ||
		(inputChar == '=') || (inputChar == '!')){
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
 * Prints the whole transition table out on stdout.
 */
void FSM::printfTransTable() {
	printf("ASCII\tSTART\tDIG_SEEN\tLTR_SEEN\tSNG_1_SEEN\tSGN_2_SEEN\tSGN_2_ERR\tCOMMENT_1\tCOMMENT_2\tCOMMENT_3\tCOMMENT_ERR\tSIGN_1_ERR\n\n");

	for(int row = 0; row < statematrix->MAX_CHARACTERS; row++) {
		printf("%d\t", row);

		for(int col = 0; col < statematrix->_MAX_STATES_; col++) {
			int printState = statematrix->transitions[row][col];
			printf("%s\t", statematrix->stateAsString((states::type_states)printState));

		}
		printf("\n");
	}
}


} // namespace statemachine
