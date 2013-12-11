/*
 * Scanner.cpp
 *
 *  Created on: 06.11.2013
 *      Author: typical
 */

#include "../include/Scanner.hpp"
#include <string.h>
#include <climits>

Scanner::Scanner() {
	statemachine = NULL;
	characterBuffer = NULL;
	bufferClass = NULL;
	symtable = NULL;
	bufIndexer = 0;
	isOverflow = false;

}
Scanner::~Scanner() {
	if(characterBuffer != NULL) {
		delete characterBuffer;
	}
	if(bufferClass != NULL) {
		delete bufferClass;
	}
	symtable = NULL;
}

ScannerError::type_t Scanner::init(const char* path, Symtable* symtable) {

	characterBuffer = (char*) malloc(BUFSIZE);
	if((characterBuffer == NULL) || (symtable == NULL)) {
		return ScannerError::NULL_POINTER;
	}

	statemachine = new statemachine::FSM();
	bufferClass = new buffer::Buffer();
	this->symtable = symtable;

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

	infoPtr_t info;

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

			/*	when characterBuffer was too small	*/
			if(isOverflow) {
				info = symtable->insert("<Integer too long>", tokentype::ERROR);

				if(!token_out.generateERROR(info, FSMRet.currentRow, FSMRet.currentColumn)) {
					return ScannerError::TOKEN_GEN_ERR;
				}
			} else {
				long value = strtol(characterBuffer, NULL, 0);

				/*	when value wasn't converted successfully	*/
				if((value == LONG_MAX) || (value == LONG_MIN)) {
					/*	long value out of range	*/
					info = symtable->insert("<Integer too long>", tokentype::ERROR);

					if(!token_out.generateERROR(info, FSMRet.currentRow, FSMRet.currentColumn)) {
						return ScannerError::TOKEN_GEN_ERR;
					}
				}
				else if(!token_out.generateINT(value, FSMRet.currentRow, FSMRet.currentColumn)) {
					return ScannerError::TOKEN_GEN_ERR;
				}
			}

			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::IDENTIFIER_ID:
		{
			bufferClass->ungetChar(FSMRet.charsBack);

			/*	when characterBuffer was too small	*/
			if(isOverflow) {
				info = symtable->insert("<Identifier too long>", tokentype::ERROR);

				if(!token_out.generateERROR(info, FSMRet.currentRow, FSMRet.currentColumn)) {
					return ScannerError::TOKEN_GEN_ERR;
				}
			} else {
				info = symtable->insert(characterBuffer, tokentype::IDENTIFIER);

				if(!token_out.generateID(info, FSMRet.currentRow, FSMRet.currentColumn)) {
					return ScannerError::TOKEN_GEN_ERR;
				}
			}
			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SPECIAL_SIGN_1_ID:
		{
			/*	buffer.ungetchar() not necessary	*/
			if(isOverflow) {
				break;	// when BUFSIZE was reached
			}

			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			if(!token_out.generateSIGN(FSMRet.currentRow, FSMRet.currentColumn, tokentype::KEY_COMPARE)) {
				return ScannerError::TOKEN_GEN_ERR;
			}

			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SPECIAL_SIGN_2_ID:
		{
			/*	buffer.ungetchar() not necessary	*/
			if(isOverflow) {
				break;	// when BUFSIZE was reached
			}

			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			if(!token_out.generateSIGN(FSMRet.currentRow, FSMRet.currentColumn, tokentype::KEY_COMPARE_NOT)) {
				return ScannerError::TOKEN_GEN_ERR;
			}

			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::SIGN_ID:
		{
			tokentype::type_t currentType = identifySign(tempChar);

			if(isOverflow) {
				break;	// when BUFSIZE was reached
			}

			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			if(!token_out.generateSIGN(FSMRet.currentRow, FSMRet.currentColumn, currentType)) {
				return ScannerError::TOKEN_GEN_ERR;
			}

			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::COMMENT_END:
		{
			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;
		} break;
		case statemachine::FSMstatus::STEP_BACK:
		{
			bufferClass->ungetChar(FSMRet.charsBack);
			/*	erase characterBuffer	*/
			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

		} break;
		case statemachine::FSMstatus::IGNORE:
		{
			/*	a comment will be ignored, nothing to do	*/
		} break;
		case statemachine::FSMstatus::ERROR_TOK:
		{
			/*	buffer.ungetchar() not necessary	*/
			if(isOverflow) {
				break;	// when BUFSIZE was reached
			}

			ScannerError::type_t ret;
			ret = saveChar(tempChar);
			if(ret != ScannerError::OK) {
				return ret;
			}

			info = symtable->insert(characterBuffer, tokentype::ERROR);

			if(!token_out.generateERROR(info, FSMRet.currentRow, FSMRet.currentColumn)) {
				return ScannerError::TOKEN_GEN_ERR;
			}

			isOverflow = false;
			memset(characterBuffer, 0, BUFSIZE);
			bufIndexer = 0;

			return ScannerError::OK;
		} break;
		case statemachine::FSMstatus::OK:
		{
			if(isOverflow) {
				break;	// when BUFSIZE was reached
			}

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
		isOverflow = true;
		memset(characterBuffer, 0, BUFSIZE);
		bufIndexer = 0;
		//return ScannerError::TMP_BUF_TOO_SMALL;
	} else {
		characterBuffer[bufIndexer] = currentChar;
		bufIndexer++;
//		return ScannerError::OK;
	}
	return ScannerError::OK;
}

