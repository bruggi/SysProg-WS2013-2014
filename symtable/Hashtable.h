/*
 * Hashtable.h
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "Pair.h"
#include "List.h"

using namespace std;

template<class type>
class Hashtable {

	List<Pair<type> >* table; // Array mit Listen
	int size; // Länge des Arrays


	/**
	 * Generiert einen Hashcode, der sich aus der Quersummer der ASCII-Werte der einzelnen Zeichen
	 * von key ergibt.
	 */

	int hashcode(string key) {
		int hash = 0;
		for (unsigned int i = 0; i < key.length(); i++) {
			hash += (int) key[i];
		}
		return hash;
	}

	/**
	 * Sucht nach einem Pair-Objekt und gibt falls vorhanden den daraufzeigenden Iterator zurück
	 */
	ListElement<Pair<type> >* getIterator(string key) {
		ListElement<Pair<type> >* listIterator = table[hashcode(key) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			while (listIterator != table[hashcode(key) % size].end()) {
				if (key == listIterator->key) {
					return listIterator;
				}
			}
		}
	return (NULL);
	}

public:
	Hashtable(int nsize) {
		table = new List<Pair<type> > [nsize];
		size = nsize;
	}
	~Hashtable() {
		for (int i = 0; i < size; i++) {
			table[i].clear();

		}
		delete table;

		//table->clear();	//ruft die destruktoren der einzelnen elemente auf
		//delete[] table;	//macht dasselbe???
	}

	/**
	 * Legt ein neues Pair-Objekt an.
	 * Falls der key schon vorhanden ist, wird das vorhandene Objekt überschrieben
	 */
	bool put(string key, type value) {
		ListElement<Pair<type> >* listIterator = table[hashcode(key) % size].begin();
		if (!contains(key)) {
			table[hashcode(key) % size].push_back(new Pair<type> (key, value));

			cout << "angelegt" << endl;
			return false;
		} else { //wert schon vorhanden, value überschreiben
			for (int i=0; i< table[hashcode(key) % size].size();i++) {
				if (key == listIterator->getPairObject()->key) {
					listIterator->getPairObject()->value = value;
					cout << "ueberschrieben" << endl;
					return true;
				}

			}
		}
		return false;
	}

	/**
	 * Gibt zu einem übergebenen key den value zurück falls das Pair-Objekt vorhanden ist
	 */
	type get(string key) {
		ListElement<Pair<type> >* listIterator = table[hashcode(key) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			for (int i =0;i<table[hashcode(key) % size].size();i++) {
				if (key == listIterator->getPairObject()->key) {
					cout << "gesuchte Parameter: " << listIterator->getPairObject()->key << " "
							<< listIterator->getPairObject()->value << endl;
					return listIterator->getPairObject()->value;
				}
				listIterator = listIterator->getNext();
			}
		}
		return (type) -1;
	}

	/**
	 * Löscht das Pair-Objekt mit dem key falls es vorhanden ist
	 */
	bool remove(string key) {
		ListElement<Pair<type> >* listIterator = table[hashcode(key) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			for (int i =0;i< table[hashcode(key) % size].size();i++) {
				if (key == listIterator->getPairObject()->key) {
					table[hashcode(key) % size].erase(listIterator); //löscht den gesuchten Wert aus der liste
					cout << "gelöscht" << endl;

					return (!contains(key));
				}
				listIterator = listIterator->getNext();
			}
		}
		return (!contains(key));
	}

	/**
	 * Prüft, ob ein gesuchtes Pair-Objekt vorhanden ist und gibt im Erfolgsfall true zurück
	 */
	bool contains(string key) {
		ListElement<Pair<type> >* listIterator = table[hashcode(key) % size].begin();
		for (int i = 0; i < table[hashcode(key) % size].size(); i++) {
			if (key == listIterator->getPairObject()->key) {
				return true;
			}
			listIterator = listIterator->getNext();
		}
		return false;
	}

	void dump() {
		cout << "dump" << endl;
		for(int i = 0; i  < size; i++) {
			cout << i << ": ";
			for(int j = 0; j < table[i].size(); j++) {
				cout << table[i].get(j)->getPairObject()->key << " " << table[i].get(j)->getPairObject()->value << "\n";
			}
			cout << "\n";
		}

	}

};

#endif /* HASHTABLE_H_ */
