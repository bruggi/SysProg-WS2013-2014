/*
 * StatementsNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/StatementsNode.hpp"

#include "../include/Parser.hpp"
#include "../include/StatementNode.hpp"

StatementsNode::StatementsNode(Parser *parser){
	this->statement = NULL;
	this->statements = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

StatementsNode::~StatementsNode(){
	delete statement;
	delete statements;
}

void StatementsNode::typeCheck(){

	if(nodeType == ParseTree::STATEMENTS_1){
		statement->typeCheck();
		statements->typeCheck();
	}
	else if(nodeType == ParseTree::STATEMENTS_2){
		/*	epsilon	*/
	}

	this->tokType = tokentype::NO_TYPE;
}

void StatementsNode::makeCode(){

	if(nodeType == ParseTree::STATEMENTS_1){
		statement->makeCode();
		statements->makeCode();
	}
	else if(nodeType == ParseTree::STATEMENTS_2){
		parser->getFileWriter()->write("NOP");
		parser->getFileWriter()->write("\n");
	}
}


