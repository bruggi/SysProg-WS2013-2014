/*
 * Automat.hpp
 *
 *  Created on: 16.10.2013
 *      Author: typical
 *
 *      Not used!
 */

#ifndef AUTOMAT_HPP_INCLUDED
#define AUTOMAT_HPP_INCLUDED

#include "FSMError.hpp"

#include <stdio.h>

namespace statemachine {

class Automat {

private:

public:

	Automat();
	virtual ~Automat();

	virtual FSMstatus::status_struct validateChar(const char inputChar) = 0;

}; // class Automat

} // namespace statemachine

#endif /* AUTOMAT_HPP_INCLUDED */
