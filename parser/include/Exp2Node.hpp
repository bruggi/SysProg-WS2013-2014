/*
 * Exp2Node.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef EXP2NODE_HPP_INCLUDED
#define EXP2NODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;
class ExpNode;
class Token;
class IndexNode;


class Exp2Node : public ParseTree {

private:

	Parser* parser;

public:

	Exp2Node(Parser* parser);
	virtual ~Exp2Node();

	/*	following nodes	*/
	ExpNode* exp;
	Token* token;
	IndexNode* index;
	Exp2Node* exp2;


	void typeCheck();
	void makeCode();

}; // class Exp2Node


#endif /* EXP2NODE_HPP_ */
