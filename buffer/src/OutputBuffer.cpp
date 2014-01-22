/*
 * OutputBuffer.cpp
 *
 *  Created on: 24.12.2013
 *      Author: typical
 */

#include "OutputBuffer.hpp"
#include <time.h>

namespace buffer {

namespace logLevel {

const char* AsString(type_t t) {
	switch(t) {
	case DEBUG:		return "DEBUG";
	case INFO:		return "INFO";
	case ERROR:		return "ERROR";
	case FATAL:		return "FATAL";
	default:		return "UNDEF";
	} // end switch
}
} // namespace logLevel

OutputBuffer::OutputBuffer() {
	filePtr_out = NULL;
	filePtr_log = NULL;
	outBuffer_A = NULL;
	outBuffer_B = NULL;
	writeCond = PTHREAD_COND_INITIALIZER;
	cond_mutex = PTHREAD_MUTEX_INITIALIZER;
	log_mutex = PTHREAD_MUTEX_INITIALIZER;
	params_thread.buffer = NULL;
	params_thread.shouldTerminate = false;
	currentBufferID = 0;
	BUFFERSIZE = 512;
}
OutputBuffer::~OutputBuffer() {

	/*	write a last time out	*/
	params_thread.shouldTerminate = true;
	char* tempBuffer;
	if(currentBufferID % 2 == 0) {
		tempBuffer = outBuffer_B;
	} else {
		tempBuffer = outBuffer_A;
	}
	params_thread.buffer = tempBuffer;
	pthread_mutex_lock(&cond_mutex);
//	printf("Destructor: signal thread to write buffer %d\n", currentBufferID);
	pthread_cond_signal(&writeCond);
	pthread_mutex_unlock(&cond_mutex);

	pthread_join(outThread, NULL);
	fclose(filePtr_out);
	fclose(filePtr_log);
}

void* OutputBuffer::writeOutThreadWrapper(void* object) {
	(((bufferStruct*)object)->object)->writeOutThread(((bufferStruct*)object)->params);
	return NULL;
}

void OutputBuffer::writeOutThread(void* param) {

/*
 * param in threadparam casten
 * übergebenen buffer rausschreiben und danach auf signal warten
 *
 */

	threadparam* params = static_cast<threadparam*>(param);

	while(!params->shouldTerminate) {

	pthread_mutex_lock(params->cond_mutex);
	pthread_cond_wait(params->writeCond, params->cond_mutex);


	int ret = fwrite(params->buffer, sizeof(char), strlen(params->buffer), params->filePtr);
	if(ret != (int)strlen(params->buffer)) {
		printLog(logLevel::FATAL, __func__, "Not successfully written: %d of %d!", ret, (int)strlen(params->buffer));
	}

	fflush(params->filePtr);
	memset(params->buffer, 0, strlen(params->buffer));
//	printf("Thread: %d characters written.\n", ret);
	pthread_mutex_unlock(params->cond_mutex);

	}
	printLog(logLevel::INFO, __func__, "Thread terminated.");
}



/**
 * Initializes the output buffer.
 * If a param is NULL, then the kind of file output will be ignored.
 *
 * @param out_path:		path to the output file. If NULL, then no file will be created.
 * @param log_path:		path to the log file. If NULL, the no file will be created.
 *
 * @return 		true:	if everything is fine.
 * 				false:	if an error happened or a file pointer is already in use.
 */
bool OutputBuffer::init(const char* out_path, const char* log_path) {
	if( (filePtr_out != NULL) || (filePtr_log != NULL)) {
		return false;
	}

	/*	both are not NULL, open both	*/

	filePtr_log = fopen(log_path, "a");
	if(filePtr_log == NULL) {
		return false;
	}
	filePtr_out = fopen(out_path, "w");
	if(filePtr_out == NULL) {
		return false;
	}


	/*
	 * init buffers
	 */
	outBuffer_A = (char*) malloc(BUFFERSIZE);
	if(outBuffer_A == NULL) {
		return false;
	}
	outBuffer_B = (char*) malloc(BUFFERSIZE);
	if(outBuffer_B == NULL) {
		return false;
	}

	/*	create thread	*/
	params_thread.filePtr = filePtr_out;
	params_thread.BUFSIZE = BUFFERSIZE;
	params_thread.cond_mutex = &cond_mutex;
	params_thread.writeCond = &writeCond;
	wrapper.object = this;
	wrapper.params = &params_thread;
	pthread_create(&outThread, NULL, writeOutThreadWrapper, (void*) &wrapper);

	return true;
}

/**
 * Writes additional info/debug/error characters into the log file, given by
 * "OutputBuffer::init()".
 *
 * Thread-safe!!
 *
 * @param level:	the level of the informations to print.
 * @param funcName:	name of the calling function, "__func__" is recommended.
 * @param format:	format string, like printf
 * @param ...:		args, like printf
 *
 * @return		true:	if everything is fine.
 * 				false:	if an error happened.
 */
bool OutputBuffer::printLog(logLevel::type_t level, const char* funcName, const char* format, ...) {

	if( (funcName == NULL) || (format == NULL) || (filePtr_log == NULL) ) {
		return false;
	}

	pthread_mutex_lock(&log_mutex);

	/*	get local time	*/
	struct tm* timeinfo;
	time_t rawtime;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	const int BUFSIZE = 256;
	char tempBuf[BUFSIZE / 2] = {0};
	char timeBuf[80] = {0};

	strftime(timeBuf, 80, "%c", timeinfo);

	int bytesWritten = 0;

	/*	build additional informations	*/
	bytesWritten = snprintf(tempBuf, (BUFSIZE / 2) - 1, "[%s]%s::%s: %s",
							timeBuf, logLevel::AsString(level),
							funcName, format);
	if(bytesWritten >= (BUFSIZE / 2) -1) {
		/*	output truncated	*/
		/*	signal, that string would be longer with '$'	*/
		tempBuf[(BUFSIZE/2) -2] = '$';
	}
	/*	terminate string	*/
	tempBuf[(BUFSIZE / 2)] = 0;

	/*	build format string	*/
	va_list args;
	va_start(args, format);

	/*	write out	*/
	vfprintf(filePtr_log, tempBuf, args);

	va_end(args);

	/*	write newline character	*/
	fputc('\n', filePtr_log);

	/*	flush	*/
	fflush(filePtr_log);

	pthread_mutex_unlock(&log_mutex);

	return true;
}

/**
 * Writes given String into the output file given by "OutputBuffer::init()".
 *
 * @param format:	format string, like printf
 * @param ...:		args, like printf
 *
 * @return		true:	if string was written.
 * 				false:	if an error occurred.
 */
bool OutputBuffer::write(const char* format, ...) {

	if( (format == NULL) || (filePtr_out == NULL) ) {
		return false;
	}

	char* tempBuffer = NULL;
	char* temp2Buffer = NULL;

	if(currentBufferID % 2 == 0) {
		tempBuffer = outBuffer_B;
		temp2Buffer = outBuffer_B;
	} else {
		tempBuffer = outBuffer_A;
		temp2Buffer = outBuffer_A;
	}

	va_list args;
	va_start(args, format);

	tempBuffer += charactersSaved;
	usleep(100);	// wait , because main thread could be too fast.

	/*	enough characters collected, write out now	*/
	if((charactersSaved + strlen(format)) > BUFFERSIZE) {
		params_thread.buffer = temp2Buffer;
		pthread_mutex_lock(&cond_mutex);

//		printf("%lu character to write seen.\n", charactersSaved);
//		printf("signal thread for writing buffer: %d\n", currentBufferID);

		/*	signal write thread	*/
		pthread_cond_signal(&writeCond);

		pthread_mutex_unlock(&cond_mutex);
		charactersSaved = 0;

		currentBufferID = (currentBufferID % 2) + 1;
		if(currentBufferID % 2 == 0) {
			tempBuffer = outBuffer_B;
		} else {
			tempBuffer = outBuffer_A;
		}
	}

	int written = vsprintf(tempBuffer, /*strlen(format) + 1,*/ format, args);

	if(written < 0) {
		printLog(logLevel::FATAL, __func__, "Error filling tempBuffer!");
		return false;
	}

	va_end(args);

	charactersSaved += written;
	return true;
}

} // namespace buffer


