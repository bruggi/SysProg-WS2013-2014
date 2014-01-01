/*
 * ParseTree.hpp
 *
 *  Created on: 22.12.2013
 *      Author: typical
 */

#ifndef PARSETREE_HPP_INCLUDED
#define PARSETREE_HPP_INCLUDED

#include <Tokentypes.hpp>
#include <Token.hpp>
#include <OutputBuffer.hpp>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class ParseTree {

protected:



public:

	typedef enum {
		UNDEFINED = -1,			/*	undefined state						*/
		PROG = 0,
		DECLS_1 = 1,			/*	DECL; DECLS							*/
		DECLS_2 = 2,			/*	epsilon								*/
		STATEMENTS_1 = 3,		/*	STATEMENT; STATEMENTS				*/
		STATEMENTS_2 = 4,		/*	epsilon								*/
		DECL = 5,				/*	int ARRAY identifier				*/
		ARRAY_1 = 6,			/*	[integer]							*/
		ARRAY_2	= 7,			/*	epsilon								*/
		STATEMENT_1 = 8,		/*	identifier INDEX = EXP				*/
		STATEMENT_2 = 9,		/*	print(EXP)							*/
		STATEMENT_3 = 10,		/*	read(identifier INDEX)				*/
		STATEMENT_4 = 11,		/*	{STATEMENTS}						*/
		STATEMENT_5 = 12,		/*	if (EXP) STATEMENT else STATEMENT	*/
		STATEMENT_6 = 13,		/*	while(EXP) STATEMENT				*/
		EXP = 14,				/*	EXP2 OP_EXP							*/
		EXP2_1 = 15,			/*	(EXP)								*/
		EXP2_2 = 16,			/*	identifier INDEX					*/
		EXP2_3 = 17,			/*	integer								*/
		EXP2_4 = 18,			/*	- EXP2								*/
		EXP2_5 = 19,			/*	! EXP2								*/
		INDEX_1 = 20,			/*	[EXP]								*/
		INDEX_2 = 21,			/*	epsilon								*/
		OP_EXP_1 = 22,			/*	OP_EXP								*/
		OP_EXP_2 = 23,			/*	epsilon								*/
		OP_1 = 24,				/*	+	*/
		OP_2 = 25,				/*	-	*/
		OP_3 = 26,				/*	*	*/
		OP_4 = 27,				/*	/	*/
		OP_5 = 28,				/*	<	*/
		OP_6 = 29,				/*	>	*/
		OP_7 = 30,				/*	==	*/
		OP_8 = 31,				/*	=!=	*/
		OP_9 = 32,				/*	&	*/
	}nodetype;

	nodetype nodeType;
	tokentype::type_t tokType;

	ParseTree();
	virtual ~ParseTree();


}; // class ParseTree


#endif /* PARSETREE_HPP_INCLUDED */
