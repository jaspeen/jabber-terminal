/*
 * JabberShell.cpp
 *
 *  Created on: Sep 30, 2010
 *      Author: jaspeen
 */

#include "JabberTerminal.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "CSProcessor.h"

void JabberTerminal::start() {
	proc->start();

	JID ownerID(config.getOwner());
	session = new MessageSession( jabberClient, ownerID );
	session->registerMessageHandler( this );
	pthread_create(&workThread,NULL,_run_method,this);
	jabberClient->connect();

}

void JabberTerminal::stop()
{
}

static void byteout(char * buf, int size)
{
	for(int i = 0; i<size; i++)
	{
		printf("%i|",buf[i]);
	}
	printf("\n");
}

static void fixNewline(char * buf, int size)
{
	for(int i = 1; i<size; i++)
		if(buf[i-1] == 13 && buf[i] == 10)
		{
			buf[i-1] = 10;
			buf[i] = 13;
		}
}

static void fixBell(char * buf, int size)
{
	for(int i = 0; i<size; i++)
	{
		if(buf[i] == 7)
			buf[i] = 10;
	}
}

static void assignAndRemoveEscapeSeq(std::string & str, char * buf, int size)
{
	int p = 0;
	bool es = false;
	for(int i = 0; i<size; i++)
	{
		if(buf[i] == 27)
		{
			str.append(buf+p,i-p);
			es = true;
		}
		else if(es && (buf[i] <= 126 && buf[i] >= 64 && buf[i] != 91 && buf[i] != 93))
		{
			p = i+1;
			es = false;
		}
	}
	if(p < (size-1) && !es)
		str.append(buf+p,size-p);
}

void *JabberTerminal::_run_method(void *arg)
{
	sleep(3);
	JabberTerminal * jsh = (JabberTerminal*)arg;
	char *buf = new char[jsh->config.getBufferSize()];
	int n = 0;
	std::string outStr;
	while(1)
	{
		n = jsh->proc->read(buf,jsh->config.getBufferSize());
		if(n == 0)
			break;
		outStr.clear();
		CSProcessor::process(outStr,buf,n);
		//printf("Str to Send:'%s'\n",outStr.c_str());
		jsh->session->send(outStr);
		if(jsh->config.getReadTimeout())
			sleep(jsh->config.getReadTimeout());
	}
	delete [] buf;
	return NULL;
}

JabberTerminal::JabberTerminal(Config & cfg, Process * _proc)
: config(cfg),proc(_proc){

	JID cljid(config.getJid());
	jabberClient = new Client(cljid, config.getPassword());
}

void JabberTerminal::handleMessage(const Message& stanza,
            MessageSession* session)
{
	std::string toWr = stanza.body();
	toWr.append(1,'\n');
	//printf("toWrite:'%s'\n",toWr.c_str());
	proc->write((char*)toWr.c_str(),toWr.length());
	proc->flush();
}

JabberTerminal::~JabberTerminal() {
	stop();
	delete jabberClient;
}
