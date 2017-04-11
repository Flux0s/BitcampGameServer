#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>

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
	 * Default send method to relay a default to the client
	 * Returns whether an error occured
	 */
	bool send();

	/*
	 * send
	 * Default send method to relay a const void * to the client
	 */
	bool send(const char *);

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
