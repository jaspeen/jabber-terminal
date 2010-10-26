/*
 * Config.cpp
 *
 *  Created on: Oct 11, 2010
 *      Author: mironov
 */

#include "Config.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

Config::Config():readTimeout(0),bufferSize(1024) {
	// TODO Auto-generated constructor stub

}

const std::list<std::string> & Config::getArgs() const
{
    return args;
}

const std::string & Config::getExec() const
{
    return exec;
}

const std::string & Config::getJid() const
{
    return jid;
}

const std::string & Config::getOwner() const
{
    return owner;
}

const std::string & Config::getPassword() const
{
    return password;
}

const int Config::getReadTimeout() const
{
    return readTimeout;
}

const int Config::getBufferSize() const
{
    return bufferSize;
}

void Config::read(const char * file) throw (SystemException) {

	//printf("Start reading config file %s\n",file);
	FILE * f = fopen(file,"r");
	if(f == NULL)
		throw SystemException();

    char curLine[1025];
    std::string str;
    std::string key;
    std::string value;
    char * buf;
    while(true)
    {
    	buf = fgets(curLine,1024,f);
    	if(buf == NULL)
    		break;
    	//printf("Line: '%s'\n",curLine);
    	str.clear();
    	for(char * i = curLine; *i != '\0'; i++)
    		if(!isspace(*i))
    			str.append(1,*i);
    	//printf("StrippedLine: '%s'\n",str.c_str());
    	size_t separator_pos = str.find(':',0);
    	if(separator_pos != std::string::npos)
    	{
    		key = str.substr(0,separator_pos);
    		value = str.substr(separator_pos+1,str.length()-separator_pos);
    	}
    	else
    	{
    		key = str;
    	}
    	initKeyValue(key,value);
    }

	fclose(f);
}

void Config::initKeyValue(std::string & key, std::string & value)
{
	//printf("Key: %s, Value: %s",key.c_str(),value.c_str());
	if(key == CONFIG_KEY_JID)
		jid = value;
	else if(key == CONFIG_KEY_OWNER)
		owner = value;
	else if(key == CONFIG_KEY_PASSWORD)
		password = value;
	else if(key == CONFIG_KEY_EXEC)
		exec = value;
	else if(key == CONFIG_KEY_ARGS)
	{
		size_t tmp;
		for(size_t i = 0; i<value.length(); i++)
		{
			tmp = value.find(',',i);
			if(tmp == std::string::npos)
			{
				args.insert(args.end(),value.substr(i,value.length()-i));
				break;
			}
			else
			{
				args.insert(args.end(),value.substr(i,tmp));
				i = tmp;
			}
		}
	}
	else if(key == CONFIG_KEY_READ_TIMEOUT)
	{
		char * endPtr;
		int _tmp = strtol(value.c_str(),&endPtr,10);
		if(*endPtr == '\0')
			readTimeout = _tmp;
	}
	else if(key == CONFIG_KEY_BUFFER_SIZE)
	{
		char * endPtr;
		int _tmp = strtol(value.c_str(), &endPtr, 10);
		if (*endPtr == '\0')
			bufferSize = _tmp;
	}
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}
