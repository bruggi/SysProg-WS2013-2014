/*
 * main.cpp
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#include <iostream>
#include "Hashtable.h"
//fragen ob man std::string benutzen darf!

using namespace std;

int main(){
	Hashtable<unsigned long>* tabelle = new Hashtable<unsigned long>(50000000);
	cout << tabelle->contains("hallo") << endl;
	tabelle->put("hallo",10);
	tabelle->put("hallo",5);
	tabelle->put("hallofdjlksa",7);
//	tabelle->dump();
	cout << tabelle->contains("hallo") << endl;
	tabelle->get("hallo");
//	tabelle->remove("hallo");
	cout << tabelle->contains("hallo") << endl;

	tabelle->put("mimimi",555);
	tabelle->put("igigig",666);
	tabelle->put("igigi",666);
	tabelle->put("igig",666);
	tabelle->put("lglglglg",333);
	tabelle->put("schkfjdsal",88888);
	//tabelle->get("lglglglg");
	//tabelle->get("igigig");
	//tabelle->get("mimimi");
	tabelle->dump();
//	tabelle->remove("mimimi");
//	tabelle->dump();



	return 0;
}
