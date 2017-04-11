#include "Client.h"

Client::Client() {}

Client::Client(int sockfd, struct sockaddr_storage their_addr) {
	m_sockFD = sockfd;
	m_client_addr = their_addr;
}

bool Client::send() {
	int numbytes;
	std::string defaultMessage = "Default transmission";
	return (numbytes = (int) sendto(m_sockFD, defaultMessage.c_str(), sizeof(defaultMessage.c_str()), 0, ((struct sockaddr *) &m_client_addr), sizeof(struct sockaddr_storage))) == -1;
}

bool Client::send(std::string message) {
	int numbytes;
	return (numbytes = (int) sendto(m_sockFD, message.c_str(), sizeof(message.c_str()), 0, ((struct sockaddr *) &m_client_addr), sizeof(struct sockaddr_storage))) == -1;
}

std::string Client::getIP() {
	char s[INET6_ADDRSTRLEN];
	return (inet_ntop(m_client_addr.ss_family, getInAddr((struct sockaddr *) &m_client_addr), s, sizeof(s)));
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

void *Client::getInAddr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in *) sa)->sin_addr);
	}
	return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

#pragma clang diagnostic pop