/*
 * Parser.hpp
 *
 *  Created on: 24.12.2013
 *      Author: typical
 */

#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include "ArrayNode.hpp"
#include "DeclNode.hpp"
#include "DeclsNode.hpp"
#include "Exp2Node.hpp"
#include "ExpNode.hpp"
#include "IndexNode.hpp"
#include "OpExpNode.hpp"
#include "OpNode.hpp"
#include "ProgNode.hpp"
#include "StatementNode.hpp"
#include "StatementsNode.hpp"

#include <Scanner.hpp>
#include <Symtable.h>
#include <OutputBuffer.hpp>

#include <vector>

namespace parserError {
typedef enum {
	OK,
	NULL_POINTER,
	INVAL_PARAM,
	ERR_PARSE_PROG,
	ERR_PARSE_DECLS,
	ERR_PARSE_DECL,
	ERR_PARSE_ARRAY,
	ERR_PARSE_STATEMENTS,
	ERR_PARSE_STATEMENT,
	ERR_PARSE_EXP,
	ERR_PARSE_EXP2,
	ERR_PARSE_INDEX,
	ERR_PARSE_OP_EXP,
	ERR_PARSE_OP
}type_t;
const char* AsString(type_t t);
} // namespace parserError

class Parser {

private:

	Token* currentToken;
	Scanner* scanner;
	ProgNode* progTree;
	buffer::OutputBuffer* fileWriter;
	Symtable* symtable;

	std::vector<Token*> tokenVec;

	tokentype::type_t currentTokType;

	Token* getNextToken();

	parserError::type_t parse_Prog(ProgNode* prog);
	parserError::type_t parse_Decls(DeclsNode* decls);
	parserError::type_t parse_Decl(DeclNode* decl);
	parserError::type_t parse_Array(ArrayNode* array);
	parserError::type_t parse_Statements(StatementsNode* statements);
	parserError::type_t parse_Statement(StatementNode* statement);
	parserError::type_t parse_Exp(ExpNode* exp);
	parserError::type_t parse_Exp2(Exp2Node* exp2);
	parserError::type_t parse_Index(IndexNode* index);
	parserError::type_t parse_Op_Exp(Op_ExpNode* op_Exp);
	parserError::type_t parse_Op(OpNode* op);

public:

	int labelCounter;
	bool isCorrect;

	Parser();
	~Parser();

	bool init(const char* in_file, const char* out_file, const char* log_file);

	parserError::type_t parse();

	buffer::OutputBuffer* getFileWriter();

	bool typeCheck();
	void makeCode();


}; // class Parser


#endif /* PARSER_HPP_INCLUDED */
