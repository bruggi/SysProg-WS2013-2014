#include "Buffer.h"
#include "iostream"

using namespace std;

int main(int argc, char **argv) {
	int fehler = 0;
	Buffer*  buffer;

	buffer = new Buffer();

	fehler = buffer->initBuffer();
	if( fehler == -1){
		cout <<"Buffer konnte nicht initialisiert werden!";
	}

	for(int i = 0; i<1100; i++){
		cout << buffer->getChar();
	}



	delete buffer;
	return 0;

}
