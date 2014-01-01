/*
 * ArrayNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef ARRAYNODE_HPP_INCLUDED
#define ARRAYNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;

class ArrayNode : public ParseTree {

private:

	Parser* parser;

public:

	ArrayNode(Parser* parser);
	virtual ~ArrayNode();

	long integer;

	void typeCheck();
	void makeCode();


}; // class ArrayNode

#endif /* ARRAYNODE_HPP_INCLUDED */
