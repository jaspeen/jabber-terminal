/*
 * main.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: jaspeen
 */
#include "JabberTerminal.h"
#include <stdio.h>
#include "Config.h"
#include "TerminalProcess.h"
#include <errno.h>
#include <stdlib.h>

void printUsage(const char * cmd_name)
{
	printf("Usage: %s [config]\n Search places for config file: /etc/jabber-terminal.conf, $HOME/.jabber-terminal.conf",cmd_name);
}

#define CURRENT_DIR_DEFAULT_CONFIG "jabber-terminal.conf"
#define ETC_DEFAULT_CONFIG "/etc/jabber-terminal.conf"
#define HOME_DEFAULT_CONFIG "/.jabber-terminal.conf"

void tryInitDefaultConfig(Config & conf)
{
	try
	{
		const char * hm = getenv("HOME");
		if(hm == NULL)
			throw SystemException();
		std::string hc = hm;
		hc.append(HOME_DEFAULT_CONFIG);
		conf.read(hc.c_str());
	}
	catch(SystemException & e)
	{
		try{
			conf.read(ETC_DEFAULT_CONFIG);
		}catch(SystemException & e)
		{
			conf.read(CURRENT_DIR_DEFAULT_CONFIG);
		}
	}

}

int main(int argc, char ** argv)
{
	Config cfg;
	if(argc > 1)
	{
		try
		{
			cfg.read(argv[1]);
		} catch(SystemException & e)
		{
			if(e.getErrCode() == ENOENT)
				tryInitDefaultConfig(cfg);
			else
				throw;
		}
	}
	else
		tryInitDefaultConfig(cfg);



	TerminalProcess proc(cfg);


	JabberTerminal sh(cfg,&proc);
	sh.start();

}
