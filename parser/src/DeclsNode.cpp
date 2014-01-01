/*
 * DeclsNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/DeclsNode.hpp"

#include "../include/DeclNode.hpp"
#include "../include/Parser.hpp"


DeclsNode::DeclsNode(Parser* parser){
	this->decl = NULL;
	this->decls = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

DeclsNode::~DeclsNode() {
	delete decl;
	delete decls;
}

void DeclsNode::typeCheck() {

	if(nodeType == ParseTree::DECLS_1) {
		this->decl->typeCheck();
		this->decls->typeCheck();
	}
	else if(nodeType == ParseTree::DECLS_2) {
		/*	epsilon	*/
	}
	else {
		parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
						"DECLS nodeType is not defined.");
		parser->isCorrect = false;
	}

	this->tokType = tokentype::NO_TYPE;
}

void DeclsNode::makeCode(){
	if(nodeType == ParseTree::DECLS_1){
		decl->makeCode();
		decls->makeCode();
	}
	else if(nodeType == ParseTree::DECLS_2){
		/*	epsilon	*/
	}
}

