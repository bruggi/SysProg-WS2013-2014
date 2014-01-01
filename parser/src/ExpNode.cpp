/*
 * ExpNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/ExpNode.hpp"

#include "../include/Exp2Node.hpp"
#include "../include/OpExpNode.hpp"
#include "../include/Parser.hpp"

ExpNode::ExpNode(Parser* parser) {
	this->exp2 = NULL;
	this->opExp = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

ExpNode::~ExpNode() {
	delete exp2;
	delete opExp;
}

void ExpNode::typeCheck(){
	exp2->typeCheck();
	opExp->typeCheck();

	if(opExp->tokType == tokentype::NO_TYPE){
		this->tokType = exp2->tokType;
	}
	else if(exp2->tokType != opExp->tokType ){
		this->tokType = tokentype::ERROR;
		parser->isCorrect = false;
	}
	else{
		this->tokType = exp2->tokType;
	}
}

void ExpNode::makeCode(){

	if(opExp->tokType == tokentype::NO_TYPE){
		exp2->makeCode();
	}
	else if(opExp->tokType == tokentype::KEY_BRAKET_ARRW_CLOSE){
		opExp->makeCode();
		exp2->makeCode();

		parser->getFileWriter()->write("LES");
		parser->getFileWriter()->write("\n");
	}
	else if(opExp->tokType == tokentype::KEY_COMPARE_NOT){
		exp2->makeCode();
		opExp->makeCode();

		parser->getFileWriter()->write("NOT");
		parser->getFileWriter()->write("\n");
	}
	else {
		exp2->makeCode();
		opExp->makeCode();
	}

}


