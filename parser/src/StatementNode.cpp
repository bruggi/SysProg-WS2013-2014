/*
 * StatementNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/StatementNode.hpp"

#include "../include/Parser.hpp"
#include <Token.hpp>
#include "../include/IndexNode.hpp"
#include "../include/ExpNode.hpp"
#include "../include/StatementsNode.hpp"

StatementNode::StatementNode(Parser *parser) {
	this->exp = NULL;
	this->identifier = NULL;
	this->index = NULL;
	this->statement1 = NULL;
	this->statement2 = NULL;
	this->statements = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

StatementNode::~StatementNode() {
	delete exp;
	delete identifier;
	delete index;
	delete statement1;
	delete statement2;
	delete statements;

}

void StatementNode::typeCheck() {

	if(nodeType == ParseTree::STATEMENT_1) {
		index->typeCheck();
		exp->typeCheck();

		if(identifier->getInfo()->value == tokentype::NO_TYPE) {

			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"STATEMENT Identifier %s not defined. Error at row: %u column: %u",
					identifier->getInfo()->key, identifier->getRow(), identifier->getColumn() );

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else if( ( 	(exp->tokType == tokentype::INTEGER) 							&&
					(identifier->getInfo()->value == tokentype::INTEGER)	 		&&
					(index->tokType == tokentype::NO_TYPE)						)	||
				  (	(identifier->getInfo()->value == tokentype::INT_ARRAY)			&&
					(index->tokType == tokentype::ARRAY)
				  )
				){

			this->tokType = tokentype::NO_TYPE;
		}
		else {

			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"STATEMENT Incompatible types. At row: %u column: %u",
							identifier->getRow(), identifier->getColumn());

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
	}
	else if(nodeType == ParseTree::STATEMENT_2){
		exp->typeCheck();

		this->tokType = tokentype::NO_TYPE;

	}
	else if(nodeType == ParseTree::STATEMENT_3){

		index->typeCheck();

		if(identifier->getInfo()->value == tokentype::NO_TYPE){
			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"STATEMENT Identifier %s not defined. Error at row: %u column: %u",
					identifier->getInfo()->key, identifier->getRow(), identifier->getColumn() );

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else if(((identifier->getInfo()->value == tokentype::INTEGER) && index->tokType == tokentype::NO_TYPE)
				|| ((identifier->getInfo()->value == tokentype::INT_ARRAY) && index->tokType == tokentype::ARRAY)){

			this->tokType = tokentype::NO_TYPE;
		}
		else {
			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"STATEMENT Incompatible types. At row: %u column: %u",
							identifier->getRow(), identifier->getColumn());

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
	}
	else if(nodeType == ParseTree::STATEMENT_4){
		statements->typeCheck();

		this->tokType = tokentype::NO_TYPE;
	}
	else if(nodeType == ParseTree::STATEMENT_5){
		exp->typeCheck();
		statement1->typeCheck();
		statement2->typeCheck();

		if(exp->tokType == tokentype::ERROR){
			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else {
			this->tokType = tokentype::NO_TYPE;
		}
	}
	else if(nodeType == ParseTree::STATEMENT_6){
		exp->typeCheck();
		statement1->typeCheck();

		if(exp->tokType == tokentype::ERROR){
			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else {
			this->tokType = tokentype::NO_TYPE;
		}
	}
}

void StatementNode::makeCode(){

	if(nodeType == ParseTree::STATEMENT_1){
		exp->makeCode();
		parser->getFileWriter()->write("LA $");
		parser->getFileWriter()->write(identifier->getInfo()->key);
		parser->getFileWriter()->write("\n");
		index->makeCode();
		parser->getFileWriter()->write("STR");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::STATEMENT_2){
		exp->makeCode();
		parser->getFileWriter()->write("PRI");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::STATEMENT_3){
		parser->getFileWriter()->write("REA");
		parser->getFileWriter()->write("\n");

		parser->getFileWriter()->write("LA $");
		parser->getFileWriter()->write(identifier->getInfo()->key);
		parser->getFileWriter()->write("\n");
		index->makeCode();
		parser->getFileWriter()->write("STR");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::STATEMENT_4){
		statements->makeCode();
	}
	else if(nodeType == ParseTree::STATEMENT_5){
		exp->makeCode();
		int label1 = parser->labelCounter++;
		int label2 = parser->labelCounter++;

		parser->getFileWriter()->write("JIN #m");

		parser->getFileWriter()->write("%d", label1);
		parser->getFileWriter()->write("\n");

		statement1->makeCode();

		parser->getFileWriter()->write("JMP #m");

		parser->getFileWriter()->write("%d", label2);
		parser->getFileWriter()->write("\n");

		parser->getFileWriter()->write("#m");

		parser->getFileWriter()->write("%d ", label1);
		parser->getFileWriter()->write("NOP");
		parser->getFileWriter()->write("\n");

		statement2->makeCode();

		parser->getFileWriter()->write("#m");

		parser->getFileWriter()->write("%d ", label2);
		parser->getFileWriter()->write("NOP");
		parser->getFileWriter()->write("\n");

	}
	else if(nodeType == ParseTree::STATEMENT_6){

		int label1 = parser->labelCounter++;
		int label2 = parser->labelCounter++;

		parser->getFileWriter()->write("#m");

		parser->getFileWriter()->write("%d ", label1);
		parser->getFileWriter()->write("NOP");
		parser->getFileWriter()->write("\n");

		exp->makeCode();

		parser->getFileWriter()->write("JIN #m");

		parser->getFileWriter()->write("%d", label2);
		parser->getFileWriter()->write("\n");

		statement1->makeCode();

		parser->getFileWriter()->write("JMP #m");

		parser->getFileWriter()->write("%d", label1);
		parser->getFileWriter()->write("\n");

		parser->getFileWriter()->write("#m");

		parser->getFileWriter()->write("%d ", label2);
		parser->getFileWriter()->write("NOP");
		parser->getFileWriter()->write("\n");

	}
}


