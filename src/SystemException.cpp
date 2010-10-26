/*
 * SystemException.cpp
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#include "SystemException.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

SystemException::SystemException(int code) throw() {
	msg = strerror(errCode=code);

}

SystemException::SystemException() throw() {
	msg = strerror(errCode=errno);

}

const char *SystemException::what() const throw()
{
	return msg.c_str();
}


