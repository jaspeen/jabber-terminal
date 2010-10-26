/*
 * TerminalProcess.h
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#ifndef TERMINALPROCESS_H_
#define TERMINALPROCESS_H_

#include "Process.h"

class TerminalProcess: public Process {
protected:
	int master_tty;
	int slave_tty;
public:
	TerminalProcess(const Config & conf);
	virtual void start() throw (SystemException);
	//virtual void stop() throw (SystemException);
	//virtual void restart() throw (SystemException);
	virtual int read(char * buf, size_t count) throw (SystemException);
	virtual int write(char * buf, size_t count) throw (SystemException);
	virtual void flush();
	virtual ~TerminalProcess();
};

#endif /* TERMINALPROCESS_H_ */
