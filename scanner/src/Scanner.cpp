/*
 * Scanner.cpp
 *
 *  Created on: 06.11.2013
 *      Author: typical
 */

#include "../include/Scanner.hpp"
#include <string.h>

Scanner::Scanner() {
	statemachine = NULL;
	characterBuffer = NULL;
	bufferClass = NULL;
	bufIndexer = 0;

}
Scanner::~Scanner() {
	if(characterBuffer != NULL) {
		delete characterBuffer;
	}
	if(bufferClass != NULL) {
		delete bufferClass;
	}
}

ScannerError::type_t Scanner::init(const char* path) {

	characterBuffer = (char*) malloc(BUFSIZE);
	if(characterBuffer == NULL) {
		return ScannerError::NULL_POINTER;
	}

	statemachine = new statemachine::FSM();
	bufferClass = new buffer::Buffer();

	/*	init buffer for use		*/
	buffer::bufferError::type_t result = bufferClass->initBuffer(path);
	if(result != buffer::bufferError::OK) {
		return ScannerError::BUFFER_INIT_ERR;
	}

	return ScannerError::OK;
}

ScannerError::type_t Scanner::getToken(Token& token_out) {

	if((bufferClass == NULL) || (statemachine == NULL)) {
		return ScannerError::SCANNER_NOT_INIT;
	}


	while(1) {

		char tempChar = 0;
		statemachine::FSMstatus::status_struct FSMRet;
		FSMRet.returnStatus = statemachine::FSMstatus::UN_DEF;

		buffer::bufferError::type_t bufferRet = bufferClass->getChar(tempChar);
		if(bufferRet != buffer::bufferError::OK) {
			return ScannerError::BUFFER_READ_ERR;
		}


		FSMRet = statemachine->validateChar(tempChar);

		switch(FSMRet.returnStatus) {
		case statemachine::FSMstatus::INTEGER_ID:
		{
			bufferClass->ungetChar(FSMRet.charsBack);
			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, tokentype::INTEGER);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::IDENTIFIER_ID:
		{
			bufferClass->ungetChar(FSMRet.charsBack);

			/*
			 * token_out.putIntoSymTable(char*, key_identifier); // token bekommt infoObj pointer
			 */
			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, tokentype::IDENTIFIER);
			// statt tokentype::IDENTIFIER --> infotype->type


			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SPECIAL_SIGN_1_ID:
		{
			/*	buffer.ungetchar() not necessary	*/
			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, tokentype::KEY_COMPARE);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SPECIAL_SIGN_2_ID:
		{
			/*	buffer.ungetchar() not necessary	*/
			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, tokentype::KEY_COMPARE_NOT);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SIGN_ID:
		{
			tokentype::type_t currentType = identifySign(tempChar);

			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, currentType);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::COMMENT_END:
		{
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;
		} break;
		case statemachine::FSMstatus::STEP_BACK:
		{
			bufferClass->ungetChar(FSMRet.charsBack);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

		} break;
		case statemachine::FSMstatus::IGNORE:
		{
			/*	a comment will be ingnored, nothing to do	*/
		} break;
		case statemachine::FSMstatus::ERROR_TOK:
		{
			/*	buffer.ungetchar() not necessary	*/
			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			token_out.generate(characterBuffer, bufIndexer + 1, FSMRet.currentRow,
								FSMRet.currentColumn, tokentype::ERROR);
			/*	erase characterBuffer	*/
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::OK:
		{
			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}
		} break;
		case statemachine::FSMstatus::END_OF_FILE:
		{
			return ScannerError::EOF_REACHED;
		}
		default:
		{
			return ScannerError::FATAL_FSM_ERR;
		} break;
		} //  end switch


	} // end while(1)

	return ScannerError::OK;
}

tokentype::type_t Scanner::identifySign(char sign) {
	switch(sign) {
	case '+':		return tokentype::KEY_PLUS;
	case '-':		return tokentype::KEY_MINUS;
	case '<':		return tokentype::KEY_BRAKET_ARRW_OPEN;
	case '>':		return tokentype::KEY_BRAKET_ARRW_CLOSE;
	case '&':		return tokentype::KEY_AMPERSAND;
	case ';':		return tokentype::KEY_SEMICOLON;
	case '(':		return tokentype::KEY_BRAKET_RND_OPEN;
	case ')':		return tokentype::KEY_BRAKET_RND_CLOSE;
	case '{':		return tokentype::KEY_BRAKET_CLY_OPEN;
	case '}':		return tokentype::KEY_BRAKET_CLY_CLOSE;
	case '[':		return tokentype::KEY_BRAKET_SQR_OPEN;
	case ']':		return tokentype::KEY_BRAKET_SQR_CLOSE;
	case '/':		return tokentype::KEY_SLASH;
	case '*':		return tokentype::KEY_STAR;
	case '=':		return tokentype::KEY_EQUAL;
	case '!':		return tokentype::KEY_BANG;
	default:		return tokentype::UNDEFINED;
	}// end switch
	return tokentype::UNDEFINED;
}

ScannerError::type_t Scanner::saveChar(char currentChar) {
	if((bufIndexer + 1) >= BUFSIZE) {
		return ScannerError::TMP_BUF_TOO_SMALL;
	}
	characterBuffer[bufIndexer] = currentChar;
	bufIndexer++;
	return ScannerError::OK;
}

