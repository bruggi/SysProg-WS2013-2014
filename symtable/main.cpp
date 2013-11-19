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
	Hashtable<int>* tabelle = new Hashtable<int>(20);	//symboltabelle muss charpointer als value speichern funktioniert nur bei 3!!!
	cout << tabelle->contains("hallo") << endl;
	tabelle->put("hallo",10);
	tabelle->put("hallo",5);
	tabelle->put("hallofdjlksa",7);
	//tabelle->dump();
	cout << tabelle->contains("hallo") << endl;
	tabelle->get("hallo");
	tabelle->remove("hallo");
	cout << tabelle->contains("hallo") << endl;

	tabelle->put("mimimi",555);
	tabelle->put("igigig",666);
	tabelle->put("igigi",666);
	tabelle->put("igig",666);
	tabelle->put("lglglglg",333);
	tabelle->get("lglglglg");
	tabelle->get("igigig");
	tabelle->get("mimimi");
	//tabelle->dump();
	tabelle->remove("mimimi");
	tabelle->dump();



	return 0;
}
