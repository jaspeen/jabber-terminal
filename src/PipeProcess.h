/*
 * PipeProcess.h
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#ifndef PIPEPROCESS_H_
#define PIPEPROCESS_H_

#include "Process.h"

class PipeProcess: public Process {
	int fd_out[2]; /* Child stdout pipe */
	int fd_in[2]; /* Child stdin pipe */
public:
	PipeProcess(const Config & conf);
	virtual void start() throw (SystemException);
	//virtual void stop() throw (SystemException);
	//virtual void restart() throw (SystemException);
	virtual int read(char * buf, size_t count) throw (SystemException);
	virtual int write(char * buf, size_t count) throw (SystemException);
	virtual void flush();
	virtual ~PipeProcess();
};

#endif /* PIPEPROCESS_H_ */
