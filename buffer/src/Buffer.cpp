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
	bufferC = NULL;
	p_bufferA = NULL;
	p_bufferB = NULL;
	p_bufferC = NULL;

	currentPos = 0;
	wasFilled = false;
	fileId = 0;

	countChars = 0;
	counter = 0;

	pthread_mutex_init(&bufferAmutex,NULL);
	pthread_mutex_init(&bufferBmutex,NULL);
	pthread_mutex_init(&bufferCmutex,NULL);
	pthread_create(&readerThread, NULL,fillBufferVoid, NULL);

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
	ret = posix_memalign( &bufferA, getpagesize(), BUFSIZE + 1); // +1, for secured \0 adding
	if(ret != 0) {
		return bufferError::ALLOC_ERR;
	}

	ret = posix_memalign( &bufferB, getpagesize(),BUFSIZE + 1); // +1, for secured \0 adding
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
* Ließt Zeichen ein und schreibt sie in den entsprechenden Buffer.
* Zu Beginn wird BufferA gefüllt.
* Wenn keine Zeichen gelesen werden, wird die Datei geschlossen.
* Sind 512 Zeichen gelesen wird switchBuffer() aufgerufen und BufferB wird gefüllt.
*/
bufferError::type_t Buffer::fillBuffer(void* buffer){

	if(currentPos == BUFSIZE){
		pthread_mutex_lock(&bufferCmutex);
	}
	else if(currentPos == BUFSIZE * 2){
		pthread_mutex_lock(&bufferAmutex);
	}
	else if(currentPos == BUFSIZE * 3){
		pthread_mutex_lock(&bufferBmutex);
	}

	if(buffer == NULL) {
		if(currentPos == BUFSIZE){
			pthread_mutex_unlock(&bufferCmutex);
		}
		else if(currentPos == BUFSIZE * 2){
			pthread_mutex_unlock(&bufferAmutex);
		}
		else if(currentPos == BUFSIZE * 3){
			pthread_mutex_unlock(&bufferBmutex);
		}
		return bufferError::NULL_POINTER;
	}
	countChars = read(fileId, buffer, BUFSIZE);

	if(countChars == 0 ){
		close(fileId);
	}
	char* tempBuf = (char*) buffer;
	/*	wenn buffer nicht ganz gefüllt wurde, dann setzt hinten \0 drann	*/
	if(countChars < (BUFSIZE - 1)) {
		/*	currentBuffer not filled completely	*/
		tempBuf[countChars + 1] = '\0';
		close(fileId);
	}

	wasFilled = true;

	if(currentPos == BUFSIZE){
		pthread_mutex_unlock(&bufferCmutex);
	}
	else if(currentPos == BUFSIZE * 2){
		pthread_mutex_unlock(&bufferAmutex);
	}
	else if(currentPos == BUFSIZE * 3){
		pthread_mutex_unlock(&bufferBmutex);
	}

	return bufferError::OK;
}

void* Buffer::fillBufferVoid(void* buffer){
	fillBuffer(buffer);
}

/*
* Gibt ein Zeichen aus dem Buffer zurück.
* kann nicht entscheiden ob ende erreicht ist.
*/
bufferError::type_t Buffer::getChar(char& out_char){

	if(currentPos == BUFSIZE){
		pthread_mutex_lock(&bufferCmutex);
	}
	else if(currentPos == BUFSIZE * 2){
		pthread_mutex_lock(&bufferAmutex);
		}
	else if(currentPos == BUFSIZE * 3){
		pthread_mutex_lock(&bufferBmutex);
	}

	char* tempBuffer = NULL;
	int offset;
	bufferError::type_t result;

	result = getCurrentBuffer(tempBuffer, offset);
	if(result != bufferError::OK) {
		return result;
	}
	if(tempBuffer == NULL) {
		return bufferError::NULL_POINTER;
	}

	out_char = tempBuffer[currentPos - offset];
	currentPos++;

	if(currentPos == BUFSIZE){
		pthread_mutex_unlock(&bufferCmutex);
	}
	else if(currentPos == BUFSIZE * 2){
		pthread_mutex_unlock(&bufferAmutex);
	}
	else if(currentPos == BUFSIZE * 3){
		pthread_mutex_unlock(&bufferBmutex);
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
			currentPos = (BUFSIZE * 3 - 1);
//			currentPos -= 1;
		}else {
			currentPos-= 1;

		}
	}
}

//hier die if ändern und fillbuffer threaden!
bufferError::type_t Buffer::getCurrentBuffer(char*& currentBuffer, int& offset) {

	bufferError::type_t result;

	if(currentPos == BUFSIZE) {
		/*  fill C and switch to B  */
		/*	switch to B	and fill it	*/
		if(!wasFilled) {
			result = fillBuffer(bufferC);  //threading!!!
			if(result != bufferError::OK) {
				return result;
			}
			currentBuffer = p_bufferB;
			offset = BUFSIZE;
		}

	}
	else if (currentPos == BUFSIZE * 2) {
		/*  fill A and switch to C  */
		/*	switch to B and fill it	*/
		if(!wasFilled) {
			result = fillBuffer(bufferA);
			if(result != bufferError::OK) {
				return result;
			}
		}
		currentBuffer = p_bufferC;
		offset = BUFSIZE;

	}
	else if (currentPos == BUFSIZE * 3) {
		/*  fill B and switch to A  */
		/*	switch to A and fill it	*/
		if(!wasFilled) {
			result = fillBuffer(bufferB);
			if(result != bufferError::OK) {
				return result;
			}
		}
		currentBuffer = p_bufferA;
		currentPos = 0;
		offset = 0;

	}

	/*	nothing to switch	*/
	if((currentPos >= 0) && (currentPos < BUFSIZE)) {
		/*	buffer A	*/
		currentBuffer = p_bufferA;
		offset = 0;
	}
	else if((currentPos >= BUFSIZE) && (currentPos < BUFSIZE * 2 )) {
		/*	buffer B	*/
		currentBuffer = p_bufferB;
		offset = BUFSIZE;
	}
	else if((currentPos >= BUFSIZE * 2) && (currentPos >= BUFSIZE * 3)) {
		/*	buffer C	*/
		currentBuffer = p_bufferC;
		offset = BUFSIZE;
	}

	/*	to fix fillBuffer bug if currentPos = 512 before and after an ungetchar()	*/
	/*	boolean is reset in enough range so that ungetchar() woun't get us into this	*/
	if(currentPos == 500 || currentPos == 800) {
		wasFilled = false;
	}

	return bufferError::OK;

}


Buffer::~Buffer() {

	if(p_bufferA != NULL){
		delete p_bufferA;
	}

	if(p_bufferB != NULL){
		delete p_bufferB;
	}

	if(p_bufferC != NULL){
		delete p_bufferC;
	}
} 

} // namespace buffer
