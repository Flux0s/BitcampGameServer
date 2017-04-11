#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <thread>
#include <iostream>

#include "Client.h"
#include "Request.h"
#include "Game.h"

#define MAXBUFLEN 100

#define NEWCLIENT "AA"
#define STARTGAME "AB"
#define GAMEREQ "AC"
#define ENDGAME "AD"

class Server {
public:
	Server();

	Server(int, char *);

	std::thread spawn();

	void killServer();

	~Server();

private:

	int createSocket(struct addrinfo);

	int getClientNum(Client, Client *, int);

	void run();

	int const m_MAXCLIENTS;
	int m_numClients, m_sockFD;
	char *m_port;
	bool m_isRunning;
	Client *m_clients;
	std::thread m_gameThread;
	Game m_bitcampGame;
};

#endif