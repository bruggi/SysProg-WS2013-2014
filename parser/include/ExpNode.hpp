/*
 * ExpNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef EXPNODE_HPP_INCLUDED
#define EXPNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Exp2Node;
class Op_ExpNode;
class Parser;

class ExpNode : public ParseTree {

private:

	Parser* parser;

public:
	ExpNode(Parser* parser);
	virtual ~ExpNode();

	/*	following nodes	*/
	Exp2Node* exp2;
	Op_ExpNode* opExp;



	void typeCheck();
	void makeCode();


}; // class ExpNode


#endif /* EXPNODE_HPP_INCLUDED */
