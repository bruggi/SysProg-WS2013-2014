/*
 * Symtable.cpp
 *
 *  Created on: 04.12.2013
 *      Author: oo7
 */

#include "Symtable.h"

Symtable::Symtable() {
	table = new Hashtable<tokentype::type_t>(50000000);
	Pair<tokentype::type_t>* currentPair;
	/*	if	*/
	currentPair = this->insert("if",tokentype::KEY_IF);
	currentPair = this->insert("IF",tokentype::KEY_IF);

	/*	while	*/
	currentPair = this->insert("while",tokentype::KEY_WHILE);
	currentPair = this->insert("WHILE",tokentype::KEY_WHILE);

	/*	print	*/
	currentPair = this->insert("print", tokentype::KEY_PRINT);
	currentPair = this->insert("PRINT", tokentype::KEY_PRINT);

	/*	read	*/
	currentPair = this->insert("read", tokentype::KEY_READ);
	currentPair = this->insert("READ", tokentype::KEY_READ);

	/*	else	*/
	currentPair = this->insert("else", tokentype::KEY_ELSE);
	currentPair = this->insert("ELSE", tokentype::KEY_ELSE);

	/*	int	*/
	currentPair = this->insert("int", tokentype::KEY_INT);
	currentPair = this->insert("INT", tokentype::KEY_INT);

}

Symtable::~Symtable() {
	//delete Hashtable;
}

Pair<tokentype::type_t>* Symtable::insert(const char* key, tokentype::type_t type){
	if(!table->put(key,type)){
		cerr << "Problem with saving key in Symtable!";
		}
	return table->get(key);
};
