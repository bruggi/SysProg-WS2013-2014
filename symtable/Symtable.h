/*
 * Symtable.h
 *
 *  Created on: 04.12.2013
 *      Author: oo7
 */

#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include "Hashtable.h"
#include "../scanner/include/Tokentypes.hpp"
#include "Pair.h"


class Symtable {
private:
	Hashtable<tokentype::type_t>* table;
public:

	Symtable();
	virtual ~Symtable();

	Pair<tokentype::type_t>* insert(const char*, tokentype::type_t);

};

#endif /* SYMTABLE_H_ */
