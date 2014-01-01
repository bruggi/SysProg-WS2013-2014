/*
 * ArrayNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/ArrayNode.hpp"
#include "../include/Parser.hpp"

ArrayNode::ArrayNode(Parser* parser) {
	this->integer = 0;
	this->tokType = tokentype::UNDEFINED;
	this->nodeType = ParseTree::UNDEFINED;
	this->parser = parser;

}

ArrayNode::~ArrayNode() {

}

void ArrayNode::typeCheck(){
	if(nodeType == ParseTree::ARRAY_1) {
		if(this->integer > 0) {
			this->tokType = tokentype::ARRAY;
		}
		else {
			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"ARRAY no valid dimension.");
			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
	}
	else if(nodeType == ParseTree::ARRAY_2){
		this->tokType = tokentype::NO_TYPE;
	}
}

void ArrayNode::makeCode(){
	if(nodeType == ParseTree::ARRAY_1){

		parser->getFileWriter()->write("%ld", integer);
	}
	else if(nodeType == ParseTree::ARRAY_2){

		parser->getFileWriter()->write("1");
		parser->getFileWriter()->write("\n");
	}
}


