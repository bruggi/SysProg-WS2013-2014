/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 *
 */

#include "Buffer.h"

Buffer::Buffer() {
	bufferA = NULL;
	bufferB = NULL;

	initBuffer();
	currentPos = 0;
	actualBuffer = 0;

	}


/*
 *	Speicher wird für BufferA und bufferB allokiert.
 *		getpagesize() returns the number of bytes in an memory page.
 *
 *	void Buffer wird zu char gecasted und pbuffer zugewiesen.
 *	Danach wird open aufgerufen.
 *	Überprüfung ob beide Speicherbereiche erfolgreich allokiert wurden. (erfolgreich liefert 0 zurück ).
 */
int Buffer::initBuffer(){
		int ret = 0, ret2 = 0;
		ret = posix_memalign( &bufferA, getpagesize(), BUFFERSIZE);
		ret2 = posix_memalign( &bufferB, getpagesize(),BUFFERSIZE);

		pbufferA = (char*)bufferA;
		pbufferB = (char*)bufferB;

		openFile();

      if (ret != 0  || ret2 != 0){
    	  return -1;
      }else {
    	  return 1;
      }


}

/*
 * Öffnet Datei. Ruft fillBuffer() auf.
 * Gibt Fehler aus falls Datei nicht geöffnet werden kann.
 */
void Buffer::openFile(){
		filePath = "/home/wei-nad/Dokumente/text.txt";
       	fileId = open(filePath , O_DIRECT | O_RDONLY);

       	if(fileId == -1){
       		cout << "DU hast etwas falsch gemacht!!Fehler beim oeffnen der Datei!";
       	}

       	fillBuffer(bufferA);
       	fillBuffer(bufferB);
}

/*
 * Wechselt Buffer, wenn 512 Zeichen eingelesen sind.
 */
void Buffer::switchBuffer(){

	if(currentPos == 1023){
			currentPos = 0;
			fillBuffer(bufferA);
	}else if (currentPos == 511){
			fillBuffer(bufferB);
	}

//	if(actualBuffer == 0){
//		fillBuffer(bufferB);
//		actualBuffer = 1;
//
//	}else if (actualBuffer == 1){
//		fillBuffer(bufferA);
//		actualBuffer = 0;
//	}
}

/*
 * Ließt Zeichen ein und schreibt sie in den entsprechenden Buffer.
 * Zu Beginn wird BufferA gefüllt.
 * Wenn keine Zeichen gelesen werden, wird die Datei geschlossen.
 * Sind 512 Zeichen gelesen wird switchBuffer() aufgerufen und BufferB wird gefüllt.
 */
void Buffer::fillBuffer( void*  buffer){

    countChars =  read(fileId, buffer, 512);

    if(countChars == 0 ){ 	//Schließen wenn kein Zeichen mehr da ist
    	if(currentPos <511){
    		pbufferA[currentPos+1] = '\0';
    	} else if (currentPos<1023){
    		pbufferB[currentPos-512 + 1] ='\0';
    	}else if(currentPos == 1023){
    		pbufferA[0] ='\0';
    	}

  	close(fileId);
  }

}

/*
 * Gibt ein Zeichen aus dem Buffer zurück.
 * kann nicht entscheiden ob ende erreicht ist.
 */
char Buffer::getChar(){

	char c;
	if(currentPos <512){
		c = pbufferA[currentPos];
		currentPos++;
	}else{
		c = pbufferB[currentPos-512];
		currentPos++;
	}
	switchBuffer();
	return c;
}


/*
 * Beim Aufrufen von ungetChar() geht currentPos eine Stelle zurück,
 * ist currentPos jedoch an der ersten Position in BufferA dann muss zurückgegangen werden
 * auf die letzte Stelle von BufferB
 */
void Buffer::ungetChar(){

	if(currentPos == 0){
		currentPos = 1023;
	}else {
		currentPos--;
	}
}


Buffer::~Buffer() {
	// TODO Auto-generated destructor stub


		if(pbufferA != 0){
			delete pbufferA;
		}

		if(pbufferB != 0){
			delete pbufferB;
		}


}
