/*
 * Exp2Node.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/Exp2Node.hpp"

#include "../include/Parser.hpp"
#include "../include/ExpNode.hpp"
#include <Token.hpp>
#include "../include/IndexNode.hpp"


Exp2Node::Exp2Node(Parser* parser) {
	this->index = NULL;
	this->token = NULL;
	this->exp2 = NULL;
	this->exp = NULL;
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

Exp2Node::~Exp2Node() {
	delete index;
	delete token;
	delete exp2;
	delete exp;
}

void Exp2Node::typeCheck(){

	if(this->nodeType == ParseTree::EXP2_1){
		exp->typeCheck();

		this->tokType = exp->tokType;
	}
	else if(nodeType == ParseTree::EXP2_2){
		index->typeCheck();

		if(token->getInfo()->value == tokentype::NO_TYPE){

			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
					"EXP2 Identifier %s not defined. Error at row: %u column: %u\n",
					token->getInfo()->key, token->getRow(), token->getColumn() );

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else if((token->getInfo()->value == tokentype::INTEGER) &&
				(index->tokType == tokentype::NO_TYPE)) {
			this->tokType = token->getInfo()->value;
		}
		else if((token->getInfo()->value == tokentype::INT_ARRAY) &&
				(index->tokType == tokentype::ARRAY)) {
			this->tokType = tokentype::INT_ARRAY;
			// Fehler in Folie? Seite 42 steht this.type = intType?intArrayType?
		}
		else {

			parser->getFileWriter()->printLog(buffer::logLevel::ERROR, __func__,
							"EXP2 no primitive type.");

			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
	}
	else if(nodeType == ParseTree::EXP2_3){

		this->tokType = tokentype::INTEGER;
	}
	else if(nodeType == ParseTree::EXP2_4){

		exp2->typeCheck();

		this->tokType = exp2->tokType;
	}
	else if(nodeType == ParseTree::EXP2_5){
		exp2->typeCheck();

		if(exp2->tokType != tokentype::INTEGER){
			this->tokType = tokentype::ERROR;
			parser->isCorrect = false;
		}
		else{
			this->tokType = tokentype::INTEGER;
		}
	}
}

void Exp2Node::makeCode(){
	if(nodeType == ParseTree::EXP2_1){
		exp->makeCode();
	}
	else if(nodeType == ParseTree::EXP2_2){
		parser->getFileWriter()->write("LA $");
		parser->getFileWriter()->write(token->getInfo()->key);
		parser->getFileWriter()->write("\n");

		index->makeCode();

		parser->getFileWriter()->write("LV");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::EXP2_3){
		parser->getFileWriter()->write("LC ");

		parser->getFileWriter()->write("%ld", token->getValue());
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::EXP2_4){
		parser->getFileWriter()->write("LC 0");
		parser->getFileWriter()->write("\n");

		exp2->makeCode();

		parser->getFileWriter()->write("SUB");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::EXP2_5){
		exp2->makeCode();

		parser->getFileWriter()->write("NOT");
		parser->getFileWriter()->write("\n");
	}
}


