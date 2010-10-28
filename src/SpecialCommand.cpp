/*
 * SpecialCommand.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: mironov
 */

#include "SpecialCommand.h"
#include <signal.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

SpecialCommand::SpecialCommand(const std::string & line) {
	// TODO Auto-generated constructor stub
	parse(line);
}

void SpecialCommand::parse(const std::string & line)
{
	//Parse command

	bool wordStart = false;
	size_t i = 0;
	for(i = 0; i<line.length(); i++)
	{
		if(wordStart)
		{
			if(!isspace(line[i]))
			{
				cmd.append(1,line[i]);
			}
			else
			{
				wordStart = false;
				break;
			}
		}
		else if(!isspace(line[i]))
		{
			cmd.append(1,line[i]);
			wordStart = true;
		}
	}

	//Parse arguments
	wordStart = false;
	for (; i < line.length(); i++) {
		if (wordStart) {
			if (!isspace(line[i])) {
				args.back().append(1, line[i]);
			} else {
				wordStart = false;
				break;
			}
		} else if (!isspace(line[i])) {
			args.push_back("");
			args.back().append(1, line[i]);
			wordStart = true;
		}
	}


}

void SpecialCommand::execute(JabberTerminal & jt) throw (SystemException)
{
	if(cmd == "kill")
	{
		int signum = SIGTERM;
		if(args.size() > 0)
			signum = atoi(args.front().c_str());
		kill(jt.getProcess()->getPid(),signum);
	}
	else if(cmd == "cc")
	{
		if(!args.empty())
		{
			size_t i = 0;
			char * c_seq = new char[args.size()];
			for(std::list<std::string>::iterator iter = args.begin(); iter != args.end() && i < args.size(); iter++,i++)
			{
				c_seq[i] = atoi(args.front().c_str());
			}
			jt.getProcess()->write(c_seq,args.size());
		}
	}
}

SpecialCommand::~SpecialCommand() {
	// TODO Auto-generated destructor stub
}
