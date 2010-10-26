/*
 * TerminalProcess.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */

#include "TerminalProcess.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pty.h>
#include <utmp.h>
#include <termios.h>

TerminalProcess::TerminalProcess(const Config & conf):
Process(conf) {
	// TODO Auto-generated constructor stub

}

TerminalProcess::~TerminalProcess() {
	// TODO Auto-generated destructor stub
}

int TerminalProcess::read(char *buf, size_t count) throw(SystemException) {
	int n = 0;
	if ((n = ::read(master_tty, buf, count)) < 0) {
		throw SystemException();
	}
	return n;
}

int TerminalProcess::write(char * buf, size_t count) throw(SystemException)
{
	int n = 0;
	if ((n = ::write(master_tty, buf, count)) < 0) {
		throw SystemException();
	}
	return n;
}

void TerminalProcess::flush()
{
	fsync(master_tty);
	fdatasync(master_tty);
}

void TerminalProcess::start() throw (SystemException) {
	if (0 != openpty(&master_tty, &slave_tty, NULL, NULL, NULL))
		throw SystemException();

	switch (cpid = fork()) {
	case -1:
		throw SystemException();
	case 0:
		//setsid();
		struct termios tty_conf;
		login_tty(slave_tty);
		tcgetattr(slave_tty,&tty_conf);
		tty_conf.c_lflag &= !ECHO;
		tcsetattr(slave_tty,TCSANOW,&tty_conf);
		//if (dup2(STDOUT_FILENO, STDERR_FILENO) == -1) {
		//			throw SystemException();
		//		}
		//setvbuf(stdout, (char*) NULL, _IONBF, 0);

		exec_child();
		break;

	default:
		//close(fd_out[1]);
		//close(fd_in[0]);
		printf("Process %s started\n", config.getExec().c_str());
	}
}
