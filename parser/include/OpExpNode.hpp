/*
 * OpExpNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef OPEXPNODE_HPP_INCLUDED
#define OPEXPNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class OpNode;
class Parser;
class ExpNode;

class Op_ExpNode : public ParseTree {

private:

	Parser* parser;

public:

	Op_ExpNode(Parser* parser);
	virtual ~Op_ExpNode();

	/*	following nodes	*/
	OpNode* op;
	ExpNode* exp;


	void typeCheck();
	void makeCode();

}; // class ParseTree


#endif /* OPEXPNODE_HPP_INCLUDED */
