/*
 * OpExpNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/OpExpNode.hpp"

#include "../include/OpNode.hpp"
#include "../include/Parser.hpp"
#include "../include/ExpNode.hpp"

Op_ExpNode::Op_ExpNode(Parser* parser) {
	this->op = NULL;
	this->exp = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

Op_ExpNode::~Op_ExpNode() {
	delete op;
	delete exp;
}

void Op_ExpNode::typeCheck(){

	if(nodeType == ParseTree::OP_EXP_1){
		op->typeCheck();
		exp->typeCheck();

		this->tokType = exp->tokType;
	}
	else if(nodeType == ParseTree::OP_EXP_2){
		this->tokType = tokentype::NO_TYPE;
	}
}

void Op_ExpNode::makeCode(){
	if(nodeType == ParseTree::OP_EXP_1){
		exp->makeCode();
		op->makeCode();
	}
	else if(nodeType == ParseTree::OP_EXP_2){
		/*	epsilon	*/
	}
}
