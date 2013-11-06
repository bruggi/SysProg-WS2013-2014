/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>   //für posix_memalign
using namespace std;

#include <unistd.h>

#define BUFFERSIZE 512

class Buffer {
private:

	void* bufferA;
	void* bufferB;

	char* pbufferA;
	char* pbufferB;
	int currentPos;
	int fileId;
	int actualBuffer; // 0 = BufferA, 1=BufferB

	const char *filePath;
	ssize_t countChars;	//kann minus wert zurückgeben
	size_t counter;		//Zählt bis zu Bufferende



public:
	Buffer();
	virtual ~Buffer();
	void fillBuffer(void* buffer);
	char getChar();
	void switchBuffer();
	void ungetChar( );
	int initBuffer();
	void openFile();

};

#endif /* BUFFER_H_ */
