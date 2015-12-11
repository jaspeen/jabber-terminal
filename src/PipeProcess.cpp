/*
 * PipeProcess.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#include "PipeProcess.h"
#include <stdio.h>
#include <unistd.h>

PipeProcess::PipeProcess(const Config & conf):
Process(conf) {
	// TODO Auto-generated constructor stub

}


PipeProcess::~PipeProcess() {
	// TODO Auto-generated destructor stub
}

int PipeProcess::read(char *buf, size_t count) throw(SystemException) {
	int n = 0;
	if ((n = ::read(fd_out[0], buf, count)) < 0) {
		throw SystemException();
	}
	return n;
}

int PipeProcess::write(char * buf, size_t count) throw(SystemException)
{
	int n = 0;
	if ((n = ::write(fd_in[1], buf, count)) < 0) {
		throw SystemException();
	}
	return n;
}

void PipeProcess::flush()
{
	fsync(fd_in[1]);
	fdatasync(fd_in[1]);
	fsync(fd_out[0]);
    fdatasync(fd_out[0]);
}

void PipeProcess::start() throw(SystemException){

	if (pipe(fd_out) != 0) {
		throw SystemException();
	}

	if (pipe(fd_in) != 0) {
		throw SystemException();
	}

	switch (cpid = fork()) {
	case -1:
		throw SystemException();
	case 0:
		if (dup2(fd_out[1], STDOUT_FILENO) == -1) {
			throw SystemException();
		}
		//if (dup2(fd_out[1], STDERR_FILENO) == -1) {
		//	throw SystemException();
		//}
		if (dup2(fd_in[0], STDIN_FILENO) == -1) {
			throw SystemException();
		}
		close(fd_out[0]);
		close(fd_out[1]);
		close(fd_in[0]);
		close(fd_in[1]);

		setvbuf(stdout,(char*)NULL,_IONBF,0);

		exec_child();
		break;

	default:
		close(fd_out[1]);
		close(fd_in[0]);
		printf("Process %s Started\n",config.getExec().c_str());
	}
}
