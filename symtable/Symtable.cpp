/*
 * Symtable.cpp
 *
 *  Created on: 04.12.2013
 *      Author: oo7
 */

#include "Symtable.h"

Symtable::Symtable() {
	table = new Hashtable<tokentype::type_t>(50000000);
	this->insert("if",tokentype::KEY_IF);
	this->insert("IF",tokentype::KEY_IF);
	this->insert("while",tokentype::KEY_WHILE);
	this->insert("WHILE",tokentype::KEY_WHILE);

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
