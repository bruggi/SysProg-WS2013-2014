/*
 * ScannerError.hpp
 *
 *  Created on: 25.10.2013
 *      Author: typical
 */

#ifndef SCANNERERROR_HPP_INCLUDED
#define SCANNERERROR_HPP_INCLUDED

namespace ScannerError {

typedef enum {
	OK = 0,
	NULL_POINTER = -1,
	INVALID_PARAM = -2,
	SCANNER_NOT_INIT = -3,
	BUFFER_INIT_ERR = -4

}type_t;

} // namespace ScannerError

#endif /* SCANNERERROR_HPP_ */
