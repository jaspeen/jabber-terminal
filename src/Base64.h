/*
 * Base64.h
 *
 *  Created on: Oct 5, 2010
 *      Author: jaspeen
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <string>

class Base64 {
public:
	static std::string encode(unsigned char const* , unsigned int len);
	static std::string decode(std::string const& s);
};

#endif /* BASE64_H_ */
