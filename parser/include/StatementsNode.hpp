/*
 * StatementsNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef STATEMENTSNODE_HPP_INCLUDED
#define STATEMENTSNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;
class StatementNode;

class StatementsNode : public ParseTree {

private:

	Parser* parser;

public:
	StatementsNode(Parser* parser);
	virtual ~StatementsNode();

	/*	following nodes	*/
	StatementNode* statement;
	StatementsNode* statements;


	void typeCheck();
	void makeCode();


}; // class StatementsNode


#endif /* STATEMENTSNODE_HPP_INCLUDED */
