/*
 * OutputBuffer.hpp
 *
 *  Created on: 24.12.2013
 *      Author: typical
 */

#ifndef OUTPUTBUFFER_HPP_INCLUDED
#define OUTPUTBUFFER_HPP_INCLUDED

#include <stdio.h>
#include <stdarg.h>

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


public:

	OutputBuffer();
	~OutputBuffer();

	bool init(const char* out_path, const char* log_path);

	bool printLog(logLevel::type_t level, const char* funcName, const char* format, ...);

	bool write(const char* format, ...);


}; // class OutputBuffer

} // namespace buffer


#endif /* OUTPUTBUFFER_HPP_INCLUDED */
