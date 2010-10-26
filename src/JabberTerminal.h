/*
 * JabberShell.h
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#ifndef JABBERSHELL_H_
#define JABBERSHELL_H_

#include <string>
#include <pthread.h>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/messagesession.h>
#include "Process.h"
#include "Config.h"

using namespace gloox;

class JabberTerminal : public MessageHandler {
protected:
	Config config;
	Client* jabberClient;
	MessageSession * session;
	Process * proc;
	static void* _run_method(void * jsh);
	pthread_t workThread;
public:
	JabberTerminal(Config & cfg, Process * _proc);
	void start();
	void stop();
	virtual void handleMessage(const Message& stanza,
	            MessageSession* session = 0);
	virtual ~JabberTerminal();
};

#endif /* JABBERSHELL_H_ */
