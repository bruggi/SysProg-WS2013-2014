/*
 * OutputBuffer.hpp
 *
 *  Created on: 24.12.2013
 *      Author: typical
 */

#ifndef OUTPUTBUFFER_HPP_INCLUDED
#define OUTPUTBUFFER_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

namespace buffer {

namespace logLevel {
typedef enum {
	DEBUG,
	INFO,
	ERROR,
	FATAL
}type_t;

const char* AsString(type_t t);

} // namespace logLevel

class OutputBuffer {

private:

	FILE* filePtr_out;
	FILE* filePtr_log;

	char* outBuffer_A;	// 1--> ID
	char* outBuffer_B;	// 2--> ID
	int currentBufferID;
	size_t BUFFERSIZE;
	size_t charactersSaved;

	struct threadparam {
		char* buffer;
		bool shouldTerminate;
		FILE* filePtr;
		size_t BUFSIZE;
		pthread_mutex_t* cond_mutex;
		pthread_cond_t* writeCond;
		pthread_mutex_t* ready_mutex;
	};

	struct bufferStruct {
		OutputBuffer* object;
		threadparam* params;
	};

	threadparam params_thread;
	bufferStruct wrapper;

	pthread_cond_t writeCond;
	pthread_mutex_t cond_mutex;
	pthread_mutex_t ready_mutex;
	pthread_t outThread;

	pthread_mutex_t log_mutex;


	void writeOutThread(void* param);
	static void* writeOutThreadWrapper(void* object);

public:

	OutputBuffer();
	~OutputBuffer();

	bool init(const char* out_path, const char* log_path);

	bool printLog(logLevel::type_t level, const char* funcName, const char* format, ...);

	bool write(const char* format, ...);


}; // class OutputBuffer

} // namespace buffer


#endif /* OUTPUTBUFFER_HPP_INCLUDED */
