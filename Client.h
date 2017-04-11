#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>

class Client {
public:
	/*
	 * Client
	 * Unused default constructor
	 */
	Client();

	/*
	 * Client
	 * Constructor that creates a
	 */
	Client(int, struct sockaddr_storage);

	/*
	 * send
	 * Default send method to relay a void * to the client
	 * Returns whether an error occured
	 */
	bool send();

	/*
	 * send
	 * Default send method to relay a void * to the client
	 */
	bool send(const void *);

	/*
	 * getIP
	 * Returns the ip address of the client
	 */
	std::string getIP();

private:

	/*
	 * getInAddr
	 * private method that returns the void* (array) of
	 */
	void *getInAddr(struct sockaddr *sa);

	int m_sockFD;
	struct sockaddr_storage m_client_addr;
};

#endif
