/*
 * SpecialCommand.h
 *
 *  Created on: Oct 28, 2010
 *      Author: mironov
 */

#ifndef SPECIALCOMMAND_H_
#define SPECIALCOMMAND_H_

#include <string>
#include <list>
#include "JabberTerminal.h"

class SpecialCommand {
	std::string cmd;
	std::list<std::string> args;
public:
	SpecialCommand(const std::string & line);
	~SpecialCommand();

	void parse(const std::string & line);
	const std::string & getCmd() const {return cmd;}
	const std::list<std::string> & getArgs() const {return args;}
	void execute(JabberTerminal & jt) throw(SystemException);
};

#endif /* SPECIALCOMMAND_H_ */
