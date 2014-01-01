/*
 * ProgNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef PROGNODE_HPP_INCLUDED
#define PROGNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class StatementsNode;
class DeclsNode;
class Parser;


class ProgNode : public ParseTree {

private:

	Parser *parser;

public:

	ProgNode(Parser *parser);
	~ProgNode();

	/*	following nodes	*/
	StatementsNode* statements;
	DeclsNode* decls;


	void typeCheck();
	void makeCode();

}; // class ProgNode


#endif /* PROGNODE_HPP_INCLUDED */
