/*
* Buffer.cpp
*
* Created on: 2013.10.01
* Author: Esra
*
*/

#include "Buffer.h"

namespace buffer {

Buffer::Buffer() {
	bufferA = NULL;
	bufferB = NULL;
	p_bufferA = NULL;
	p_bufferB = NULL;

	currentPos = 0;
	actualBuffer = 0;
	fileId = 0;
}

/*
* Öffnet Datei. Ruft fillBuffer() auf.
* Gibt Fehler aus falls Datei nicht geöffnet werden kann.
*/
bufferError::type_t Buffer::openFile(const char* path){

	if(path == NULL) {
		return bufferError::NULL_POINTER;
	}

	fileId = open(path , O_DIRECT | O_RDONLY);

	if(fileId == -1){
		return bufferError::OPEN_ERR;
	}

	bufferError::type_t ret;

	ret = fillBuffer(bufferA);
	if(ret != bufferError::OK) {
		return ret;
	}

	ret = fillBuffer(bufferB);
	if(ret != bufferError::OK) {
		return ret;
	}

	return bufferError::OK;
}

/*
*        Speicher wird für BufferA und bufferB allokiert.
*                getpagesize() returns the number of bytes in an memory page.
*
*        void Buffer wird zu char gecasted und pbuffer zugewiesen.
*        Danach wird open aufgerufen.
*        Überprüfung ob beide Speicherbereiche erfolgreich allokiert wurden. (erfolgreich liefert 0 zurück ).
*/
bufferError::type_t Buffer::initBuffer(const char* path){

	if(path == NULL) {
		return bufferError::NULL_POINTER;
	}

	int ret;
	ret = posix_memalign( &bufferA, getpagesize(), BUFSIZE);
	if(ret != 0) {
		return bufferError::ALLOC_ERR;
	}

	ret = posix_memalign( &bufferB, getpagesize(),BUFSIZE);
	if(ret != 0) {
		return bufferError::ALLOC_ERR;
	}

	p_bufferA = (char*)bufferA;
	p_bufferB = (char*)bufferB;

	bufferError::type_t openRet;
	openRet = openFile(path);
	if(openRet != bufferError::OK) {
		return openRet;
	}

	return bufferError::OK;

}

/*
* Wechselt Buffer, wenn 512 Zeichen eingelesen sind.
*/
bufferError::type_t Buffer::switchBuffer(){

	if(currentPos == (BUFSIZE * 2 - 1)){
		currentPos = 0;
		bufferError::type_t ret = fillBuffer(bufferA);
		if(ret != bufferError::OK) {
			return ret;
		}
	}else if (currentPos == (BUFSIZE - 1)){
		bufferError::type_t ret = fillBuffer(bufferB);
		if(ret != bufferError::OK) {
			return ret;
		}
	}

//        if(actualBuffer == 0){
//                fillBuffer(bufferB);
//                actualBuffer = 1;
//
//        }else if (actualBuffer == 1){
//                fillBuffer(bufferA);
//                actualBuffer = 0;
//        }

	return bufferError::OK;
}

/*
* Ließt Zeichen ein und schreibt sie in den entsprechenden Buffer.
* Zu Beginn wird BufferA gefüllt.
* Wenn keine Zeichen gelesen werden, wird die Datei geschlossen.
* Sind 512 Zeichen gelesen wird switchBuffer() aufgerufen und BufferB wird gefüllt.
*/
bufferError::type_t Buffer::fillBuffer(void* buffer){

	if(buffer == NULL) {
		return bufferError::NULL_POINTER;
	}
	countChars = read(fileId, buffer, BUFSIZE);

	if(countChars == 0 ){
		close(fileId);
	}
	if(countChars < (BUFSIZE -1)){
		p_bufferA[countChars] = '\0'; // countChars+1?
		 close(fileId);
	} else if(((BUFSIZE-1)+ countChars) < (BUFSIZE * 2 -1)){
		p_bufferB[countChars] ='\0'; //countChars+1
		 close(fileId);
	}

//	if(countChars == 0 ){         //Schließen wenn kein Zeichen mehr da sind
//		if(currentPos < (BUFSIZE - 1)){
//				p_bufferA[currentPos+1] = '\0';
//		} else if (currentPos< (BUFSIZE * 2 - 1)){
//				p_bufferB[currentPos-BUFSIZE + 1] ='\0';
//		} else if(currentPos == (BUFSIZE * 2 - 1)){
//				p_bufferA[0] ='\0';
//		}
//	}
//	  close(fileId);
//	}

	return bufferError::OK;
}

/*
* Gibt ein Zeichen aus dem Buffer zurück.
* kann nicht entscheiden ob ende erreicht ist.
*/
bufferError::type_t Buffer::getChar(char& out_char){

	if((p_bufferA[currentPos] == '\0') || (p_bufferB[currentPos] == '\0')) {
		out_char = '\0';
	}

	if(currentPos < BUFSIZE){
		out_char = p_bufferA[currentPos];
		currentPos++;
	} else {
		out_char = p_bufferB[currentPos - BUFSIZE];
		if(currentPos == 1024 && (++currentPos =! '\0')){
			currentPos = 0;
		}
		currentPos++;
	}

	bufferError::type_t ret = switchBuffer();
	if(ret != bufferError::OK) {
		return ret;
	}

	return bufferError::OK;
}


/*
* Beim Aufrufen von ungetChar() geht currentPos eine Stelle zurück,
* ist currentPos jedoch an der ersten Position in BufferA dann muss zurückgegangen werden
* auf die letzte Stelle von BufferB
*/
void Buffer::ungetChar(size_t stepsBack){

	for (int i = stepsBack; i > 0; i--) {
		if(currentPos == 0){
				currentPos = (BUFSIZE * 2 - 1);
				currentPos -= 1;
		}else {
				currentPos-= 1;

		}
	}
}


Buffer::~Buffer() {

	if(p_bufferA != NULL){
		delete p_bufferA;
	}

	if(p_bufferB != NULL){
		delete p_bufferB;
	}
} 

} // namespace buffer
