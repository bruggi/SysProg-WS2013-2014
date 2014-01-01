/*
 * StatementNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef STATEMENTNODE_HPP_INCLUDED
#define STATEMENTNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;
class Token;
class IndexNode;
class ExpNode;
class StatementsNode;

class StatementNode : public ParseTree {

private:

	Parser* parser;

public:

	StatementNode(Parser* parser);
	virtual ~StatementNode();

	/*	following nodes	*/
	Token* identifier;
	IndexNode* index;
	ExpNode* exp;
	StatementsNode* statements;
	StatementNode* statement1;
	StatementNode* statement2;


	void typeCheck();
	void makeCode();

}; // class StatementNode


#endif /* STATEMENTNODE_HPP_INCLUDED */
