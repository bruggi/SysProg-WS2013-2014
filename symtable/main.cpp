/*
 * main.cpp
 *
 *  Created on: 04.01.2012
 *      Author: bruggi
 */

#include <iostream>
#include "Hashtable.h"
#include "../scanner/include/Tokentypes.hpp"
//fragen ob man std::string benutzen darf!

using namespace std;

int main(){
	Hashtable<tokentype::type_t>* tabelle = new Hashtable<tokentype::type_t>(50000000);
	cout << tabelle->contains("hallo") << endl;
	tabelle->put("hallo",tokentype::KEY_MINUS);
	tabelle->put("hallo",tokentype::KEY_BANG);
	tabelle->put("hallofdjlksa",tokentype::KEY_AMPERSAND);
//	tabelle->dump();
	cout << tabelle->contains("hallo") << endl;
	tabelle->get("hallo");
//	tabelle->remove("hallo");
	cout << tabelle->contains("hallofdjlksa") << endl;

//	tabelle->put("mimimi",555);
//	tabelle->put("igigig",666);
//	tabelle->put("igigi",666);
//	tabelle->put("igig",666);
//	tabelle->put("lglglglg",333);
//	tabelle->put("schkfjdsal",88888);
	//tabelle->get("lglglglg");
	//tabelle->get("igigig");
	//tabelle->get("mimimi");
	tabelle->dump();
//	tabelle->remove("mimimi");
//	tabelle->dump();



	return 0;
}
