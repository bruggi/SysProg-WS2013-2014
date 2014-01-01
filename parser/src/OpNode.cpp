/*
 * OpNode.cpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#include "../include/OpNode.hpp"

#include "../include/Parser.hpp"

OpNode::OpNode(Parser* parser) {
	this->nodeType = ParseTree::UNDEFINED;
	this->tokType = tokentype::UNDEFINED;
	this->parser = parser;
}

OpNode::~OpNode() {

}

void OpNode::typeCheck() {

	if(nodeType == ParseTree::OP_1) {
		this->tokType = tokentype::KEY_PLUS;
	}
	else if(nodeType == ParseTree::OP_2){
		this->tokType = tokentype::KEY_MINUS;
	}
	else if(nodeType == ParseTree::OP_3){
		this->tokType = tokentype::KEY_STAR;
	}
	else if(nodeType == ParseTree::OP_4){
		this->tokType = tokentype::KEY_SLASH;
	}
	else if(nodeType == ParseTree::OP_5){
		this->tokType = tokentype::KEY_BRAKET_ARRW_OPEN;
	}
	else if(nodeType == ParseTree::OP_6){
		this->tokType = tokentype::KEY_BRAKET_ARRW_CLOSE;
	}
	else if(nodeType == ParseTree::OP_7){
		this->tokType = tokentype::KEY_COMPARE;
	}
	else if(nodeType == ParseTree::OP_8){
		this->tokType = tokentype::KEY_COMPARE_NOT;
	}
	else if(nodeType == ParseTree::OP_9){
		this->tokType = tokentype::KEY_AMPERSAND;

	}
}

void OpNode::makeCode(){

	if(nodeType == ParseTree::OP_1){			/*	plus	*/
		parser->getFileWriter()->write("ADD");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_2){		/*	minus	*/
		parser->getFileWriter()->write("SUB");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_3){		/*	star	*/
		parser->getFileWriter()->write("MUL");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_4){		/*	slash	*/
		parser->getFileWriter()->write("DIV");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_5){		/*	arrow braket open	*/
		parser->getFileWriter()->write("LES");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_6){		/*	arrow braket close	*/

	}
	else if(nodeType == ParseTree::OP_7){		/*	compare	*/
		parser->getFileWriter()->write("EQU");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_8){		/*	compare not	*/
		parser->getFileWriter()->write("EQU");
		parser->getFileWriter()->write("\n");
	}
	else if(nodeType == ParseTree::OP_9){		/*	ampersand	*/
		parser->getFileWriter()->write("AND");
		parser->getFileWriter()->write("\n");
	}
}
