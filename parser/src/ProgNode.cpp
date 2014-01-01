/*
 * ProgNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/ProgNode.hpp"

#include "../include/StatementsNode.hpp"
#include "../include/DeclsNode.hpp"
#include "../include/Parser.hpp"


ProgNode::ProgNode(Parser *parser) {
	this->statements = NULL;
	this->decls = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

ProgNode::~ProgNode(){
	delete statements;
	delete decls;
}

void ProgNode::typeCheck() {

	decls->typeCheck();
	statements->typeCheck();
	this->tokType = tokentype::NO_TYPE;
}

void ProgNode::makeCode(){
	decls->makeCode();
	statements->makeCode();

	parser->getFileWriter()->write("STP");
	parser->getFileWriter()->write("\n");

}


