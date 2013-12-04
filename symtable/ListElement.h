/*
 * ListElement.h
 *
 *  Created on: 08.01.2012
 *      Author: bruggi
 */

#ifndef LISTELEMENT_H_
#define LISTELEMENT_H_s

#include "List.h"
using namespace std;

template<class type>
class List;

template<class type>
class ListElement {
	friend class List<type> ;

	ListElement<type>* prev;
	ListElement<type>* next;


public:

	type* pairObject;

	ListElement() {
		prev = next = NULL;
		pairObject = NULL;
	}
	ListElement(type* value, ListElement<type>* prev = NULL) {
		this->pairObject = value;
		this->prev = prev;
		this->next = NULL;
    }

    ListElement<type> *getNext() const
    {
        return next;
    }

    ListElement<type> *getPrev() const
    {
        return prev;
    }

    type *getPairObject() const
    {
        return pairObject;
    }

    void setNext(ListElement<type> *next)
    {
        this->next = next;
    }

    void setPrev(ListElement<type> *prev)
    {
        this->prev = prev;
    }

    void setPairObject(type *value)
    {
        this->pairObject = value;
    }

};
#endif /* LISTELEMENT_H_ */
