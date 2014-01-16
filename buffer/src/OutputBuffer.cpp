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
}
OutputBuffer::~OutputBuffer() {
	fclose(filePtr_out);
	fclose(filePtr_log);
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

	/*	open only log file	*/
	if(out_path == NULL) {

		filePtr_log = fopen(log_path, "a");
		if(filePtr_log == NULL) {
			return false;
		}
		return true;
	}

	/*	open only out file	*/
	if(log_path == NULL) {

		filePtr_out = fopen(out_path, "w");
		if(filePtr_out == NULL) {
			return false;
		}
		return true;
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

	return true;
}

/**
 * Writes additional info/debug/error characters into the log file, given by
 * "OutputBuffer::init()".
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

	va_list args;
	va_start(args, format);

	vfprintf(filePtr_out, format, args);

	va_end(args);

	return true;
}

} // namespace buffer


