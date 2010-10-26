/*
 * CSProcessor.h
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#ifndef CSPROCESSOR_H_
#define CSPROCESSOR_H_

#include <string>

class CSProcessor {
	enum SequenceType {None, Hunch, Escape, Control} seqType;
public:
	//CSProcessor():seqType(None){};
	//virtual bool onEscapeSequence(char * seq, size_t size){return false;};
	//virtual bool onControlSequence(char * seq, size_t size){return false;};
	static void process(std::string & out, char * data, int size);
	//virtual ~CSProcessor(){};
};

#endif /* CSPROCESSOR_H_ */
