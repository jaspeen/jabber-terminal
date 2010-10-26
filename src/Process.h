/*
 * Process.h
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "SystemException.h"
#include <list>
#include "Config.h"

class Process {
protected:
	Config config;
	pid_t cpid;
	void exec_child() throw(SystemException);
public:
	Process(const Config & conf);
	virtual void start() throw(SystemException) = 0;
	virtual void stop() throw(SystemException);
	virtual void restart() throw(SystemException){};
	virtual int read(char * buf, size_t count) throw(SystemException) = 0;
	virtual int write(char * buf, size_t count) throw(SystemException) = 0;
	virtual void flush() = 0;

	const Config & getConfig(){return config;}
	virtual ~Process();
};

#endif /* PROCESS_H_ */
