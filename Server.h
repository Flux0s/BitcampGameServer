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

	/*
	 * Server
	 * Default server constructor (unused)
	 */
	Server();

	/*
	 * Server
	 * Constructor - creates a socket with the given number of clients and port
	 */
	Server(int, char *);

	/*
	 * spawn
	 * Returns a thread that listens for incoming clients on the server's socket
	 */
	std::thread spawn();

	/*
	 * killServer
	 * Ends the server and game safely (closes the socket)
	 */
	void killServer();

	/*
	 * ~Server
	 * Deconstructs the server
	 */
	~Server();

private:

	/*
	 * createSocket
	 * creates a socket, called by the constructor
	 */
	int createSocket(struct addrinfo);

	/*
	 * getClientNum
	 * Returns the index of the client + 1 or -1 if the client has never connected before
	 */
	int getClientNum(Client, Client *, int);

	/*
	 * run
	 * The method that runs when a thread is created on the server (listens for new clients and handles client requests)
	 */
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