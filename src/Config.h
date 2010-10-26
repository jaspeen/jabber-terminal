/*
 * Config.h
 *
 *  Created on: Oct 11, 2010
 *      Author: mironov
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <list>
#include "SystemException.h"

#define CONFIG_KEY_JID "jid"
#define CONFIG_KEY_PASSWORD "password"
#define CONFIG_KEY_OWNER "owner"
#define CONFIG_KEY_EXEC "exec"
#define CONFIG_KEY_ARGS "args"
#define CONFIG_KEY_READ_TIMEOUT "readTimeout"
#define CONFIG_KEY_BUFFER_SIZE "bufferSize"

class Config {
protected:
	std::string jid;
	std::string password;
	std::string owner;
	std::string exec;
	std::list<std::string> args;
	int readTimeout;
	int bufferSize;
	void initKeyValue(std::string & key, std::string & value);
public:
	Config();
	~Config();
    const std::list<std::string> & getArgs() const;
    const std::string & getExec() const;
    const std::string & getJid() const;
    const std::string & getOwner() const;
    const std::string & getPassword() const;
    const int getReadTimeout() const;
    const int getBufferSize() const;

    void read(const char * file) throw(SystemException);
};

#endif /* CONFIG_H_ */
