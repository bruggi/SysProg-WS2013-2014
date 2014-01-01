/*
 * OpNode.hpp
 *
 *  Created on: 23.12.2013
 *      Author: typical
 */

#ifndef OPNODE_HPP_INCLUDED
#define OPNODE_HPP_INCLUDED

#include "ParseTree.hpp"

class Parser;

class OpNode : public ParseTree {

private:

	Parser* parser;

public:

	OpNode(Parser* parser);
	virtual ~OpNode();


	void typeCheck();
	void makeCode();

}; // class OpNode


#endif /* OPNODE_HPP_INCLUDED */
