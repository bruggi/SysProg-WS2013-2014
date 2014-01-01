/*
 * Parser.cpp
 *
 *  Created on: 24.12.2013
 *      Author: typical
 */

#include "../include/Parser.hpp"

namespace parserError {
const char* AsString(type_t t) {
	switch(t) {
	case OK:					return "OK";
	case NULL_POINTER:			return "NULL_POINTER";
	case INVAL_PARAM:			return "Invalid parameter(s)";
	case ERR_PARSE_PROG:		return "Error parsing PROG";
	case ERR_PARSE_DECLS:		return "Error parsing DECLS";
	case ERR_PARSE_DECL:		return "Error parsing DECL";
	case ERR_PARSE_ARRAY:		return "Error parsing ARRAY";
	case ERR_PARSE_STATEMENTS:	return "Error parsing STATEMENTS";
	case ERR_PARSE_STATEMENT:	return "Error parsing STATEMENT";
	case ERR_PARSE_EXP:			return "Error parsing EXP";
	case ERR_PARSE_EXP2:		return "Error parsing EXP2";
	case ERR_PARSE_INDEX:		return "Error parsing INDEX";
	case ERR_PARSE_OP_EXP:		return "Error parsing OP_EXP";
	case ERR_PARSE_OP:			return "Error parsing OP";
	default:					return "Undefined Error";
	} // end switch
}

} // namespace parserError

Parser::Parser() {
	currentToken = NULL;
	scanner = NULL;
	progTree = NULL;
	fileWriter = NULL;
	symtable = NULL;

	currentTokType = tokentype::UNDEFINED;
	isCorrect = true;
	labelCounter = 0;
}

Parser::~Parser() {
	delete currentToken;
	delete scanner;
	delete progTree;
	delete fileWriter;
	delete symtable;
	for(size_t i = 0; i < tokenVec.size(); i++) {
		delete tokenVec[i];
	}
}

Token* Parser::getNextToken() {

	ScannerError::type_t result;
	Token* currentToken = new Token();

	result = scanner->getToken(*currentToken);
	if( !(result == ScannerError::OK || result == ScannerError::EOF_REACHED) ) {
		fileWriter->printLog(buffer::logLevel::FATAL, __func__,
						"ScannerError: %s", ScannerError::AsString(result));
		return NULL;
	}

	tokenVec.push_back(currentToken);
	return currentToken;
}

bool Parser::init(const char* in_file, const char* out_file, const char* log_file) {
	if( (in_file == NULL) || (out_file == NULL) ) {
		return false;
	}
	scanner = new Scanner();
	symtable = new Symtable();
	fileWriter = new buffer::OutputBuffer();
	if(!fileWriter->init(out_file, log_file)) {
		return false;
	}

	ScannerError::type_t result;
	result = scanner->init(in_file, symtable);
	if(result != ScannerError::OK) {
		fileWriter->printLog(buffer::logLevel::FATAL, __func__,
						"Scanner init error: %s(%d)", ScannerError::AsString(result),
						result);
		return false;
	}

	fileWriter->printLog(buffer::logLevel::INFO, __func__,
						"Parser successfully initialized.");

	return true;
}



parserError::type_t Parser::parse() {
	parserError::type_t parseResult;

	this->progTree = new ProgNode(this);
	currentToken = getNextToken();
	if(currentToken == NULL) {
		return parserError::NULL_POINTER;
	}

	parseResult = this->parse_Prog(this->progTree);

	return parseResult;
}

parserError::type_t Parser::parse_Prog(ProgNode* prog) {
	parserError::type_t parseResult;

	currentTokType = currentToken->getType();

	prog->decls = new DeclsNode(this);
	prog->statements = new StatementsNode(this);

	if(	currentTokType == tokentype::IDENTIFIER 			||
		currentTokType == tokentype::KEY_PRINT 				||
		currentTokType == tokentype::KEY_READ 				||
		currentTokType == tokentype::KEY_INT				||
		currentTokType == tokentype::KEY_IF 				||
		currentTokType == tokentype::KEY_WHILE 				||
		currentTokType == tokentype::KEY_BRAKET_CLY_OPEN	||
		currentTokType == tokentype::END_OF_FILE
	){

		/*	parse DECLS		*/
		parseResult = this->parse_Decls(prog->decls);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		/*	parse STATEMENTS		*/
		parseResult = this->parse_Statements(prog->statements);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		prog->nodeType = ParseTree::PROG;

		return parserError::OK;
	}
	else {

		fileWriter->printLog(buffer::logLevel::FATAL, __func__,
						"No valid Source at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_PROG;
	}
}

parserError::type_t Parser::parse_Decls(DeclsNode* decls) {
	parserError::type_t parseResult;

	decls->decl = new DeclNode(this);
	decls->decls = new DeclsNode(this);


	if(currentTokType == tokentype::KEY_INT) {

		parseResult = this->parse_Decl(decls->decl);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_SEMICOLON) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = parse_Decls(decls->decls);
			if(parseResult != parserError::OK) {
				return parseResult;
			}

			decls->nodeType = ParseTree::DECLS_1;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Missing ';' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_DECLS;
		}
	}

	else if(currentTokType == tokentype::IDENTIFIER 			||
			currentTokType == tokentype::KEY_PRINT 				||
			currentTokType == tokentype::KEY_READ				||
			currentTokType == tokentype::KEY_BRAKET_CLY_OPEN	||
			currentTokType == tokentype::KEY_IF 				||
			currentTokType == tokentype::KEY_WHILE
			) {

		decls->nodeType = ParseTree::DECLS_2;
	}
	else if(currentTokType == tokentype::END_OF_FILE) {
		/*	end	*/

		decls->nodeType = ParseTree::DECLS_2;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"Expected declaration at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_DECLS;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Decl(DeclNode* decl) {
	parserError::type_t parseResult;

	if(currentTokType == tokentype::KEY_INT) {
		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		decl->array = new ArrayNode(this);

		parseResult = this->parse_Array(decl->array);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::IDENTIFIER) {
			decl->identifier = currentToken;

			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			decl->nodeType = ParseTree::DECL;
		}
		else{
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"No identifier found at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_DECL;
		}
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"Unknown datatype at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_DECL;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Array(ArrayNode* array){

	if(currentTokType == tokentype::KEY_BRAKET_SQR_OPEN) {

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		if(currentTokType == tokentype::INTEGER) {

			array->integer = currentToken->getValue();

			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			if(currentTokType == tokentype::KEY_BRAKET_SQR_CLOSE) {
				currentToken = getNextToken();
				if(currentToken == NULL) {
					return parserError::NULL_POINTER;
				}
				currentTokType = currentToken->getType();

				array->nodeType = ParseTree::ARRAY_1;
			}
			else {
				fileWriter->printLog(buffer::logLevel::ERROR, __func__,
								"Expected ']' at Row: %u Column: %u",
								currentToken->getRow(), currentToken->getColumn());

				return parserError::ERR_PARSE_ARRAY;
			}
		}
		else{
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"No valid Array found at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_ARRAY;
		}
	}
	else if(currentTokType == tokentype::IDENTIFIER) { // Follow
		array->nodeType = ParseTree::ARRAY_2;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"Expected Array at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_ARRAY;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Statements(StatementsNode* statements){
	parserError::type_t parseResult;

	if(currentTokType != tokentype::END_OF_FILE) {
		statements->statement = new StatementNode(this);
	}

	statements->statements = new StatementsNode(this);

	if(	currentTokType == tokentype::IDENTIFIER		||
		currentTokType == tokentype::KEY_PRINT		||
		currentTokType == tokentype::KEY_READ		||
		currentTokType == tokentype::KEY_IF			||
		currentTokType == tokentype::KEY_WHILE		||
		currentTokType == tokentype::KEY_BRAKET_CLY_OPEN
	  ) {
		parseResult = this->parse_Statement(statements->statement);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_SEMICOLON) {

			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Statements(statements->statements);
			if(parseResult != parserError::OK) {
				return parseResult;
			}

			statements->nodeType = ParseTree::STATEMENTS_1;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Missing ';' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENTS;
		}
	}
	else if(currentTokType == tokentype::KEY_BRAKET_CLY_CLOSE) {
		statements->nodeType = ParseTree::STATEMENTS_1;
	}
	else if(currentTokType == tokentype::END_OF_FILE) {
		statements->nodeType = ParseTree::STATEMENTS_2;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"Statement expected at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_STATEMENTS;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Statement(StatementNode* statement){
	parserError::type_t parseResult;

	if(currentTokType == tokentype::IDENTIFIER) {
		statement->identifier = this->currentToken;

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		statement->index = new IndexNode(this);
		statement->exp = new ExpNode(this);

		parseResult = this->parse_Index(statement->index);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_EQUAL) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Exp(statement->exp);
			if(parseResult != parserError::OK) {
				return parseResult;
			}
		}
		statement->nodeType = ParseTree::STATEMENT_1;
	}
	else if(currentTokType == tokentype::KEY_PRINT) {

		statement->exp = new ExpNode(this);

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		if(currentTokType == tokentype::KEY_BRAKET_RND_OPEN) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Exp(statement->exp);
			if(parseResult != parserError::OK) {
				return parseResult;
			}
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected '(' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}

		if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			statement->nodeType = ParseTree::STATEMENT_2;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected ')' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}
	}
	else if(currentTokType == tokentype::KEY_READ) {

		statement->index = new IndexNode(this);

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		if(currentTokType == tokentype::KEY_BRAKET_RND_OPEN) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			if(currentTokType == tokentype::IDENTIFIER) {
				statement->identifier = currentToken;

				currentToken = getNextToken();
				if(currentToken == NULL) {
					return parserError::NULL_POINTER;
				}
				currentTokType = currentToken->getType();

				parseResult = this->parse_Index(statement->index);
				if(parseResult != parserError::OK) {
					return parseResult;
				}
			}
			else {
				fileWriter->printLog(buffer::logLevel::ERROR, __func__,
								"No identifier found at Row: %u Column: %u",
								currentToken->getRow(), currentToken->getColumn());

				return parserError::ERR_PARSE_STATEMENT;
			}

			if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE) {

				currentToken = getNextToken();
				if(currentToken == NULL) {
					return parserError::NULL_POINTER;
				}
				currentTokType = currentToken->getType();

				statement->nodeType = ParseTree::STATEMENT_3;
			}
			else {
				fileWriter->printLog(buffer::logLevel::ERROR, __func__,
								"Expected ')' at Row: %u Column: %u",
								currentToken->getRow(), currentToken->getColumn());

				return parserError::ERR_PARSE_STATEMENT;
			}
		}
	}
	else if(currentTokType == tokentype::KEY_BRAKET_CLY_OPEN) {
		statement->statements = new StatementsNode(this);
		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		parseResult = this->parse_Statements(statement->statements);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_BRAKET_CLY_CLOSE) {
			/*	needed for follow	*/
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			statement->nodeType = ParseTree::STATEMENT_4;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected '}' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}
	}
	else if(currentTokType == tokentype::KEY_IF) {

		statement->exp = new ExpNode(this);
		statement->statement1 = new StatementNode(this);
		statement->statement2 = new StatementNode(this);

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		if(currentTokType == tokentype::KEY_BRAKET_RND_OPEN) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Exp(statement->exp);
			if(parseResult != parserError::OK) {
				return parseResult;
			}
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected '(' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}

		if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Statement(statement->statement1);
			if(parseResult != parserError::OK) {
				return parseResult;
			}
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected ')' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}

		if(currentTokType == tokentype::KEY_ELSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();
			parseResult = this->parse_Statement(statement->statement2);
			if(parseResult != parserError::OK) {
				return parseResult;
			}

			statement->nodeType = ParseTree::STATEMENT_5;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"No 'else' found at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}
	}
	else if(currentTokType == tokentype::KEY_WHILE) {
		statement->exp = new ExpNode(this);
		statement->statement1 = new StatementNode(this);

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		if(currentTokType == tokentype::KEY_BRAKET_RND_OPEN){
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Exp(statement->exp);
			if(parseResult != parserError::OK) {
				return parseResult;
			}
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected '(' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}


		if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			parseResult = this->parse_Statement(statement->statement1);
			if(parseResult != parserError::OK) {
				return parseResult;
			}

			statement->nodeType = ParseTree::STATEMENT_6;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected ')' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_STATEMENT;
		}
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"No valid statement found at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_STATEMENT;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Exp(ExpNode* exp) {
	parserError::type_t parseResult;

	exp->exp2 = new Exp2Node(this);
	exp->opExp = new Op_ExpNode(this);

	if(	currentTokType == tokentype::KEY_BRAKET_RND_OPEN 	||
		currentTokType == tokentype::IDENTIFIER				||
		currentTokType == tokentype::INTEGER				||
		currentTokType == tokentype::KEY_MINUS			 	||
		currentTokType == tokentype::KEY_BANG
		) {

		parseResult = this->parse_Exp2(exp->exp2);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		parseResult = this->parse_Op_Exp(exp->opExp);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		exp->nodeType = ParseTree::EXP;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"No valid expression at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_EXP;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Exp2(Exp2Node* exp2) {
	parserError::type_t parseResult;

	if(currentTokType == tokentype::KEY_BRAKET_RND_OPEN) {
		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		exp2->exp = new ExpNode(this);

		parseResult = this->parse_Exp(exp2->exp);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			exp2->nodeType = ParseTree::EXP2_1;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected ')' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_EXP2;
		}
	}
	else if(currentTokType == tokentype::IDENTIFIER) {
		exp2->token = currentToken;

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		exp2->index = new IndexNode(this);

		parseResult = this->parse_Index(exp2->index);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		exp2->nodeType = ParseTree::EXP2_2;

	}
	else if(currentTokType == tokentype::INTEGER) {
		exp2->token = currentToken;
		exp2->nodeType = ParseTree::EXP2_3;

		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();
	}
	else if(currentTokType == tokentype::KEY_MINUS) {
		currentToken = getNextToken();
		currentTokType = currentToken->getType();

		exp2->exp2 = new Exp2Node(this);

		parseResult = this->parse_Exp2(exp2->exp2);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		exp2->nodeType = ParseTree::EXP2_4;
	}
	else if(currentTokType == tokentype::KEY_BANG) {
		currentToken = getNextToken();
		currentTokType = currentToken->getType();

		exp2->exp2 = new Exp2Node(this);

		parseResult = this->parse_Exp2(exp2->exp2);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		exp2->nodeType = ParseTree::EXP2_5;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"No valid expression at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_EXP2;
	}
	return parserError::OK;
}
parserError::type_t Parser::parse_Index(IndexNode* index) {
	parserError::type_t parseResult;

	index->exp = new ExpNode(this);

	if(currentTokType == tokentype::KEY_BRAKET_SQR_OPEN) {
		currentToken = getNextToken();
		if(currentToken == NULL) {
			return parserError::NULL_POINTER;
		}
		currentTokType = currentToken->getType();

		parseResult = this->parse_Exp(index->exp);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		if(currentTokType == tokentype::KEY_BRAKET_SQR_CLOSE) {
			currentToken = getNextToken();
			if(currentToken == NULL) {
				return parserError::NULL_POINTER;
			}
			currentTokType = currentToken->getType();

			index->nodeType = ParseTree::INDEX_1;
		}
		else {
			fileWriter->printLog(buffer::logLevel::ERROR, __func__,
							"Expected ']' at Row: %u Column: %u",
							currentToken->getRow(), currentToken->getColumn());

			return parserError::ERR_PARSE_INDEX;
		}
	}
	else if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE	||
			currentTokType == tokentype::KEY_PLUS				||
			currentTokType == tokentype::KEY_MINUS				||
			currentTokType == tokentype::KEY_STAR				||
			currentTokType == tokentype::KEY_SLASH				||
			currentTokType == tokentype::KEY_BRAKET_ARRW_OPEN	||
			currentTokType == tokentype::KEY_BRAKET_ARRW_CLOSE	||
			currentTokType == tokentype::KEY_AMPERSAND			||
			currentTokType == tokentype::KEY_COMPARE			||
			currentTokType == tokentype::KEY_COMPARE_NOT 		||
			currentTokType == tokentype::KEY_SEMICOLON			||
			currentTokType == tokentype::KEY_BRAKET_SQR_CLOSE	||
			currentTokType == tokentype::KEY_EQUAL				||
			currentTokType == tokentype::KEY_ELSE
		){
		// Follow
		index->nodeType = ParseTree::INDEX_2;
	}
	else {
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"No valid index at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_INDEX;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Op_Exp(Op_ExpNode* opExp){
	parserError::type_t parseResult;

	opExp->op = new OpNode(this);
	opExp->exp = new ExpNode(this);

	if(	currentTokType == tokentype::KEY_PLUS 				||
		currentTokType == tokentype::KEY_MINUS				||
		currentTokType == tokentype::KEY_STAR				||
		currentTokType == tokentype::KEY_SLASH				||
		currentTokType == tokentype::KEY_BRAKET_ARRW_OPEN	||
		currentTokType == tokentype::KEY_BRAKET_ARRW_CLOSE	||
		currentTokType == tokentype::KEY_AMPERSAND			||
		currentTokType == tokentype::KEY_COMPARE 			||
		currentTokType == tokentype::KEY_COMPARE_NOT
		){

		parseResult = this->parse_Op(opExp->op);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		parseResult = this->parse_Exp(opExp->exp);
		if(parseResult != parserError::OK) {
			return parseResult;
		}

		opExp->nodeType = ParseTree::OP_EXP_1;
	}
	else if(currentTokType == tokentype::KEY_BRAKET_RND_CLOSE	||
			currentTokType == tokentype::KEY_BRAKET_SQR_CLOSE	||
			currentTokType == tokentype::KEY_SEMICOLON			||
			currentTokType == tokentype::KEY_ELSE
			) {

		opExp->nodeType = ParseTree::OP_EXP_2;
	}
	else{
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"No valid operation at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_OP_EXP;
	}
	return parserError::OK;
}

parserError::type_t Parser::parse_Op(OpNode* op) {
//	parserError::type_t parseResult;

	switch(currentTokType) {
	case tokentype::KEY_PLUS:
		op->nodeType = ParseTree::OP_1;
		break;
	case tokentype::KEY_MINUS:
		op->nodeType = ParseTree::OP_2;
		break;
	case tokentype::KEY_STAR:
		op->nodeType = ParseTree::OP_3;
		break;
	case tokentype::KEY_SLASH:
		op->nodeType = ParseTree::OP_4;
		break;
	case tokentype::KEY_BRAKET_ARRW_OPEN:
		op->nodeType = ParseTree::OP_5;
		break;
	case tokentype::KEY_BRAKET_ARRW_CLOSE:
		op->nodeType = ParseTree::OP_6;
		break;
	case tokentype::KEY_COMPARE:
		op->nodeType = ParseTree::OP_7;
		break;
	case tokentype::KEY_COMPARE_NOT:
		op->nodeType = ParseTree::OP_8;
		break;
	case tokentype::KEY_AMPERSAND:
		op->nodeType = ParseTree::OP_9;
		break;
	default:
		fileWriter->printLog(buffer::logLevel::ERROR, __func__,
						"Unknown operand at Row: %u Column: %u",
						currentToken->getRow(), currentToken->getColumn());

		return parserError::ERR_PARSE_OP;
	}
	currentToken = getNextToken();
	if(currentToken == NULL) {
		return parserError::NULL_POINTER;
	}
	currentTokType = currentToken->getType();

	return parserError::OK;
}


bool Parser::typeCheck() {
	this->progTree->typeCheck();
	return isCorrect;
}

void Parser::makeCode(){
	this->progTree->makeCode();
}


buffer::OutputBuffer* Parser::getFileWriter() {
	return fileWriter;
}


