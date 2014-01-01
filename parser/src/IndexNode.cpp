/*
 * IndexNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/IndexNode.hpp"

#include "../include/Parser.hpp"
#include "../include/ExpNode.hpp"

IndexNode::IndexNode(Parser* parser) {
	this->exp = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

IndexNode::~IndexNode() {
	delete exp;
}

void IndexNode::typeCheck(){

	if(nodeType == ParseTree::INDEX_1){
		if(exp->tokType == tokentype::ERROR){
			exp->typeCheck();
			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else{
			this->tokType = tokentype::ARRAY;
		}
	}
	else if(nodeType == ParseTree::INDEX_2){
		this->tokType = tokentype::NO_TYPE;
	}
}


void IndexNode::makeCode(){
	if(nodeType == ParseTree::INDEX_1){
		exp->makeCode();

		parser->getFileWriter()->write("ADD");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::INDEX_2){
		/*	epsilon	*/
	}
}


