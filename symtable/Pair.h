/*
 * Pair.h
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#ifndef PAIR_H_
#define PAIR_H_

#include<string>

using namespace std;

template<class type>
class Pair {

public:
	string key;
	type value;
	Pair(){
		this->key = "";
		this->value=(type)0;
	}
	Pair(string key, type value){
		this->key = key;
		this->value = value;
	}


};

#endif /* PAIR_H_ */
