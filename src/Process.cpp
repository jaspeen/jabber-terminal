/*
 * Process.cpp
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#include "Process.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void Process::exec_child() throw(SystemException)
{
	char ** c_args = new char*[config.getArgs().size() + 2];
	unsigned int i = 1;
	for (std::list<std::string>::const_iterator iter = config.getArgs().begin(); iter != config.getArgs().end(); iter++)
		c_args[i++] = strdup((*iter).c_str());
	c_args[0] = strdup(config.getExec().c_str());
	c_args[config.getArgs().size()] = NULL;
	if (execvp(config.getExec().c_str(), c_args) == -1)
		throw SystemException();
}

void Process::stop() throw(SystemException)
{
	throw SystemException(ENOSYS);
}

Process::Process(const Config & conf):config(conf){
	//printf("ExecPath: %s\n",config.getExec().c_str());
}

Process::~Process() {
}
