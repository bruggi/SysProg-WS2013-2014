/*
 * Pair.h
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#ifndef PAIR_H_
#define PAIR_H_

#include <string.h>

using namespace std;

template<class type>
class Pair {

public:
	char* key;
	type value;
	Pair(){
		this->key = "";
		this->value=(type)0;
	}
	Pair(const char* key, type value) {
		this->key = (char*) malloc(strlen(key) + 1);
		if(this->key == NULL) {
			exit(0);
		}
		memset(this->key, 0, strlen(key) + 1);
		memcpy(this->key, key, strlen(key)+1);
		this->value = value;
	}

	~Pair() {
		delete(this->key);
	}

};

#endif /* PAIR_H_ */
