/*
 * Hashtable.h
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include "Pair.h"
#include "List.h"

using namespace std;

template<class type>
class Hashtable {

	List<Pair<type> >* table; // Array mit Listen
	unsigned long size; // Länge des Arrays


	/**
	 * Generiert einen Hashcode, der sich aus der Quersummer der ASCII-Werte der einzelnen Zeichen
	 * von key ergibt.
	 */
	//int hashcode(string key) {
	//	int hash = 0;
	//	for (unsigned int i = 0; i < key.length(); i++) {
	//		hash += (int) key[i];
	//	}
	//	return hash;
	//}

	/**
	 * Neuer Ansatz, sdbm-algorythmus!
	 * Dieser Algorithmus wird in Sleepycat's Datenbank BDB (Berkeley DataBase) verwendet.
	**/
	unsigned long hashcode(unsigned char *str){
		unsigned long hash = 0;
		int c;

		while (c = *str++){
			hash = c + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}

	/**
	 * Sucht nach einem Pair-Objekt und gibt falls vorhanden den daraufzeigenden Iterator zurück
	 */
	ListElement<Pair<type> >* getIterator(const char* key) {

		//mit memcopy speicher kopieren und malloc allozieren und const char nach unsigned char kopieren und diesen verwenden
		unsigned char* unsignedKey = (unsigned char*)malloc((strlen(key)+1) * sizeof(unsigned char));
		memcpy(unsignedKey,key,strlen(key)+1);

		ListElement<Pair<type> >* listIterator = table[hashcode(unsignedKey) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			while (listIterator != table[hashcode(unsignedKey) % size].end()) {
				if (key == listIterator->key) {
					return listIterator;
				}
			}
		}
	return (NULL);
	}

public:
	Hashtable(unsigned long nsize) {
		table = new List<Pair<type> > [nsize];
		size = nsize;
	}
	~Hashtable() {
		for (unsigned long i = 0; i < size; i++) {
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
	bool put(const char* key, type value) {

		//mit memcopy speicher kopieren und malloc allozieren und const char nach unsigned char kopieren und diesen verwenden
		unsigned char* unsignedKey = (unsigned char*)malloc((strlen(key)+1) * sizeof(unsigned char));
		memcpy(unsignedKey,key,strlen(key)+1);

//		ListElement<Pair<type> >* listIterator = table[hashcode(unsignedKey) % size].begin();
		if (!contains(key)) {
			table[hashcode(unsignedKey) % size].push_back(new Pair<type> (key, value));
			cout << "angelegt" << endl;
			return true;
		} else { //wert schon vorhanden, value überschreiben
//			for (unsigned long i=0; i< table[hashcode(unsignedKey) % size].size();i++) {
//				if (key == listIterator->getPairObject()->key) {
//				listIterator->getPairObject()->value = value;
					cout << "schon vorhanden" << endl;
					return true;
//				}
//			}
		}
		return false;
	}

	/**
	 * Gibt den Pointer auf das Pair-Objekt zurück, falldas Objekt vorhanden ist
	 */
	Pair<type>* get(const char* key) {

		unsigned char* unsignedKey = (unsigned char*)malloc((strlen(key)+1) * sizeof(unsigned char));
		memcpy(unsignedKey,key,strlen(key)+1);

		ListElement<Pair<type> >* listIterator = table[hashcode(unsignedKey) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			for (int i=0;i<table[hashcode(unsignedKey) % size].size();i++) {
				if (key == listIterator->getPairObject()->key) {
					cout << "gesuchter Container: " << listIterator->getPairObject() << " "
							<< listIterator->getPairObject()->key << " " << listIterator->getPairObject()->value << endl;
					return listIterator->getPairObject();
				}
				listIterator = listIterator->getNext();
			}
		}
		return (0);
	}

	/**
	 * Löscht das Pair-Objekt mit dem key falls es vorhanden ist. Wird vermutlich nicht benötigt!
	 */
	bool remove(const char* key) {

		unsigned char* unsignedKey = (unsigned char*)malloc((strlen(key)+1) * sizeof(unsigned char));
		memcpy(unsignedKey,key,strlen(key)+1);

		ListElement<Pair<type> >* listIterator = table[hashcode(unsignedKey) % size].begin();
		if (contains(key)) { //prüft erst ob der gesuchte Wert in der Hashtabelle vorhanden ist
			for (unsigned long i = 0;i < table[hashcode(unsignedKey) % size].size();i++) {
				if (key == listIterator->getPairObject()->key) {
					table[hashcode(unsignedKey) % size].erase(listIterator); //löscht den gesuchten Wert aus der liste
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
	bool contains(const char* key) {

		unsigned char* unsignedKey = (unsigned char*)malloc((strlen(key)+1) * sizeof(unsigned char));
//		if(unsignedKey==0){
//			cerr << "malloc failed" << endl;
//			exit(0);
//		}
		memcpy(unsignedKey,key,strlen(key)+1);

		ListElement<Pair<type> >* listIterator = table[hashcode(unsignedKey) % size].begin();
		for (int i = 0; i < table[hashcode(unsignedKey) % size].size(); i++) {
			if (key == listIterator->getPairObject()->key) {
				return true;
			}
			listIterator = listIterator->getNext();
		}
		return false;
	}

	void dump() {
		cout << "dump" << endl;
		for(unsigned long i = 0; i  < size; i++) {
			if(table[i].size() > 0){
				cout << i << ": ";
				for(unsigned long j = 0; j < table[i].size(); j++) {
				cout << table[i].get(j)->getPairObject()->key << " " << table[i].get(j)->getPairObject()->value << "\n";
				}
			cout << "\n";
			}
		}
	}

};

#endif /* HASHTABLE_H_ */
