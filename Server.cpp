#include "Server.h"

Server::Server() : m_MAXCLIENTS(0) {}

Server::Server(int maxClients, char *port) : m_MAXCLIENTS(maxClients) {
	m_port = port;

	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // ipv4 only
	hints.ai_socktype = SOCK_DGRAM; // use UDP
	hints.ai_flags = AI_PASSIVE; // use my IP

	if (createSocket(hints))
		exit(1);
}

std::thread Server::spawn() {
	return (std::thread([this] { run(); }));
}

void Server::run() {
	int numbytes;
	socklen_t addr_len;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];

	m_isRunning = true;
	while (true) {
		addr_len = sizeof their_addr;
		if ((numbytes = (int) recvfrom(m_sockFD, buf, MAXBUFLEN - 1, 0, (struct sockaddr *) &their_addr, &addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
		}

		Client newClient(m_sockFD, their_addr);
		if (std::string(buf).substr(0, 2) == NEWCLIENT && getClientNum(newClient, m_clients, m_numClients) == -1 && m_numClients < m_MAXCLIENTS) {
			m_clients[m_numClients] = newClient;
			m_numClients++;
			newClient.send("You have been added as a client!");
		} else if (std::string(buf).substr(0, 2) == STARTGAME && m_numClients >= MINPLAYERS && !m_bitcampGame.isRunning() && getClientNum(newClient, m_clients, m_numClients) > 0) {
			m_bitcampGame = Game(m_numClients, m_clients);
			m_gameThread = m_bitcampGame.spawn();
		} else if (std::string(buf).substr(0, 2) == GAMEREQ && m_bitcampGame.isRunning() && getClientNum(newClient, m_clients, m_numClients) > 0) {
			Request newReq(getClientNum(newClient, m_clients, m_numClients), buf + 2, sizeof(buf) - 2);
			m_bitcampGame.addRequest(newReq);
		} else if (std::string(buf).substr(0, 2) == ENDGAME && m_bitcampGame.isRunning() && getClientNum(newClient, m_clients, m_numClients) > 0) {
			m_bitcampGame.killGame();
			if (m_gameThread.joinable())
				m_gameThread.join();

		}
	}
}

int Server::getClientNum(Client newClient, Client *clients, int numClients) {
	for (int i = 0; i < numClients; i++)
		if (newClient.getIP() == clients->getIP())
			return (i + 1);
	return (-1);
}

int Server::createSocket(struct addrinfo hints) {
	struct addrinfo *servinfo, *p;
	int rv;

	if ((rv = getaddrinfo(NULL, m_port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all possible sockets in the linked list and bind the first that works
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((m_sockFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
		if (bind(m_sockFD, p->ai_addr, p->ai_addrlen) == -1) {
			close(m_sockFD);
			perror("listener: bind");
			continue;
		}
		break;
	}

	// check if no sockets were bound
	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	// frees the address info structure
	freeaddrinfo(servinfo);
	return (0);
}

void Server::killServer() {
	close(m_sockFD);
	m_bitcampGame.killGame();
	if (m_gameThread.joinable())
		m_gameThread.join();
}

Server::~Server() {
	if (m_isRunning)
		killServer();
}