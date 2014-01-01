/*
 * DeclNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef DECLNODE_HPP_INCLUDED
#define DECLNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class ArrayNode;
class Token;
class Parser;

class DeclNode : public ParseTree {

private:

	Parser *parser;

public:

	DeclNode(Parser *parser);
	virtual ~DeclNode();

	/*	following nodes	*/
	ArrayNode* array;
	Token* identifier;

	void typeCheck();
	void makeCode();
};


#endif /* DECLNODE_HPP_INCLUDED	*/
