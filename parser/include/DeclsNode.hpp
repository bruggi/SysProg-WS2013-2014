/*
 * DeclsNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef DECLSNODE_HPP_INCLUDED
#define DECLSNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class DeclNode;
class Parser;

class DeclsNode : public ParseTree {

private:

	Parser *parser;

public:

	DeclsNode(Parser *parser);
	~DeclsNode();

	/*	following nodes	*/
	DeclsNode* decls;
	DeclNode* decl;

	void typeCheck();
	void makeCode();
};


#endif /* DECLSNODE_HPP_INCLUDED */
