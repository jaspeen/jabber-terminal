/*
 * SystemException.h
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#ifndef SYSTEMEXCEPTION_H_
#define SYSTEMEXCEPTION_H_

#include <exception>
#include <string>

class SystemException : public std::exception {
protected:
	int errCode;
	std::string msg;
public:
	/**
	 * Use code to initialize exception.
	 * @param code
	 */
	SystemException(int code) throw();
	/**
	 * Uses errno to obtain error code.
	 */
	SystemException() throw ();
	/**
	 * Returns integer error code.
	 * @return value of error code
	 */
	int getErrCode(){return errCode;}
	virtual const char* what() const throw();
	virtual ~SystemException() throw(){};
};

#endif /* SYSTEMEXCEPTION_H_ */
