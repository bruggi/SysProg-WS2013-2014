/*
 * DeclNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/DeclNode.hpp"

#include "../include/ArrayNode.hpp"
#include "../include/Parser.hpp"
#include <Token.hpp>

DeclNode::DeclNode(Parser *parser) {
	this->array = NULL;
	this->identifier = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

DeclNode::~DeclNode() {
	delete array;
	delete identifier;
}

void DeclNode::typeCheck() {

	this->array->typeCheck();

	if(identifier->getInfo()->value != tokentype::NO_TYPE) {

		parser->getFileWriter()->printLog(buffer::logLevel::INFO, __func__,
						"DECL Identifier: %s already defined.", identifier->getInfo()->key);

		this->tokType = tokentype::ERROR;
		parser->isCorrect = false;
	}
	else if(array->tokType == tokentype::ERROR) {
		this->tokType = tokentype::ERROR;
		parser->isCorrect = false;
	}
	else {
		this->tokType = tokentype::NO_TYPE;
		if(array->tokType == tokentype::ARRAY) {
			identifier->getInfo()->value = tokentype::INT_ARRAY;
		}
		else {
			identifier->getInfo()->value = tokentype::INTEGER;
		}
	}

}
void DeclNode::makeCode() {

	parser->getFileWriter()->write("DS $");
	parser->getFileWriter()->write(identifier->getInfo()->key);
	parser->getFileWriter()->write(" ");

	array->makeCode();

}



