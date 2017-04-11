#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <thread>
#include <iostream>
#include "Client.h"
#include "Game.h"

#define PORT "18888"
#define MAXBUFLEN 100
#define NEWCLIENT "AA"
#define STARTGAME "AB"
#define GAMEREQ "AC"
#define ENDGAME "AD"
#define MAXCLIENTS 5


void manualExit(bool *);

bool isAClient(Client, Client[MAXCLIENTS], int);

int main(void) {
	socklen_t addr_len;
	int numbytes;
	char buf[MAXBUFLEN];
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	struct sockaddr_storage their_addr;
	bool shutdownServer = false;
	Client clients[MAXCLIENTS];
	int numClients = 0;
	Game bitcampGame;

	std::cout << sizeof(clients);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // ipv4 only
	hints.ai_socktype = SOCK_DGRAM; // use UDP
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);
	std::thread exitThread(manualExit, &shutdownServer);

	while (!shutdownServer) {
		addr_len = sizeof their_addr;
		if ((numbytes = (int) recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *) &their_addr, &addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
		}

		Client newClient(sockfd, their_addr);
		if (std::string(buf).substr(0, 2) == NEWCLIENT && !isAClient(newClient, clients, numClients) && numClients < MAXCLIENTS) {
			clients[numClients] = newClient;
		}
		if (std::string(buf).substr(0, 2) == STARTGAME && numClients >= 2) {
			bitcampGame = Game(numClients, clients);
		}
	}

	close(sockfd);
	return 0;
}

void manualExit(bool *shutdown) {
	int closeSocket = 1;
	std::cout << "To close the connection enter 0: ";
	while (closeSocket)
		std::cin >> closeSocket;
	*shutdown = true;
}

bool isAClient(Client newClient, Client clients[MAXCLIENTS], int numClients) {
	for (int i = 0; i < numClients; i++)
		if (newClient.getIP() == clients->getIP())
			return (true);
	return (false);
}