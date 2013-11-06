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
	INVALID_PARAM = -2

}type_t;

} // namespace ScannerError

#endif /* SCANNERERROR_HPP_ */
