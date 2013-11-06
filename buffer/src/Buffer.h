 
/*
* Buffer.h
*
* Created on: 2013.10.01
* Author: Esra
*/

#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h> //für posix_memalign

namespace buffer {

namespace bufferError {

typedef enum {
	OK = 0,
	NULL_POINTER = -1,
	INVALID_PARAM = -2,
	READ_ERR = -3,
	OPEN_ERR = -4,
	ALLOC_ERR = -5
}type_t;

} // namespace bufferError

class Buffer {
private:

	void* bufferA;
	void* bufferB;

	char* p_bufferA;
	char* p_bufferB;
	size_t currentPos;
	int fileId;
	int actualBuffer; // 0 = BufferA, 1=BufferB

	size_t countChars;        //kann minus wert zurückgeben
	size_t counter;           //Zählt bis zu Bufferende

	static const size_t BUFSIZE  = 512;

	bufferError::type_t openFile(const char* path);
	bufferError::type_t switchBuffer();
	bufferError::type_t fillBuffer(void* buffer);

public:
	Buffer();
	virtual ~Buffer();

	bufferError::type_t getChar(char& out_char);
	void ungetChar(size_t stepsBack);
	bufferError::type_t initBuffer(const char* path);

};

} // namespace buffer
#endif /* BUFFER_H_INCLUDED */
