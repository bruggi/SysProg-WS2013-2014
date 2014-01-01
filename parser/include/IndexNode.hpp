/*
 * IndexNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef INDEXNODE_HPP_INCLUDED
#define INDEXNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;
class ExpNode;

class IndexNode : public ParseTree {

private:

	Parser* parser;

public:

	IndexNode(Parser* parser);
	virtual ~IndexNode();

	/*	following nodes		*/
	ExpNode* exp;



	void typeCheck();
	void makeCode();

}; // class IndexNode


#endif /* INDEXNODE_HPP_INCLUDED */
