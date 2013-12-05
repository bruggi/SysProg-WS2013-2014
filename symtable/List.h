/*
 * List.h
 *
 *  Created on: 07.01.2012
 *      Author: bruggi
 */

#ifndef LIST_H_
#define LIST_H_

#include "ListElement.h"
#include<iostream>
using namespace std;

template<class type>
class List {

	ListElement<type>* first;
	ListElement<type>* last;
	ListElement<type>* iterator;
	unsigned int elements;

public:
	List() {
		this->first = NULL;
		this->last = NULL;
		this->iterator = NULL;
		this->elements = 0;
	}

	void push_back(type* element) {
		if (elements == 0) {
			first = last = iterator = new ListElement<type> (element);
		}else if(elements == 1) {
			ListElement<type>* nLE = new ListElement<type> (element);

			last = nLE;
			last->prev = first;
			first->next = last;

		} else {
			//ListElement<type>* tmp = last;
			//last = new ListElement<type> (element, tmp);
			//tmp->setNext(last);
			ListElement<type>* nLE = new ListElement<type> (element, last);
			last->next = nLE;

			last = nLE;
			//last->setPrev(tmp);
		}
		elements++;
	}

	ListElement<type>* find(ListElement<type>* element) {
		for (unsigned int i = 0; i < elements; i++) {
			if (iterator->pairObject == element->pairObject) {
				this->iterator = this->first;
				return iterator;
			}
			this->iterator++;
		}
		this->iterator = this->first;
		cout << "Wert nicht gefunden" << endl;
		return NULL;
	}

	bool erase(ListElement<type>* element) {
		ListElement<type>* tmp = find(element);
		if (tmp == NULL) {
			cout << "Wert konnte nicht gelöscht werden" << endl;
			return false;
		}else if(tmp->getPairObject() == this->first->getPairObject() && tmp->getPairObject() == this->last->getPairObject()) {
			delete[] tmp;
			first = last = NULL;
			elements--;
		} else if (tmp->getPairObject() == this->first->getPairObject()) {
			this->first = tmp->getNext();
			tmp->next->setPrev(first);
			delete[] tmp;
			elements--;
		} else if (tmp == this->last) {
			this->last = tmp->prev;
			tmp->prev->setNext(last);
			delete[] tmp;
			elements--;
		} else {
			cerr << "This should'nt happen!1!";
		}
		return true;
	}

	ListElement<type>* begin() {
		return (this->first);
	}

	ListElement<type>* end() {
		return (this->last);
	}
	int size(){
		return elements;
	}
	void clear();

	ListElement<type>* get(int _e) {
		ListElement<type>* tmp = first;
		for(int i = 0; i < _e; i++) {
			tmp = tmp->next;
		}
		return tmp;
	}
};

#endif /* LIST_H_ */
