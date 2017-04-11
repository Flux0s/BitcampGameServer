#include <thread>
#include <iostream>

#include "Game.h"
#include "Server.h"

#define PORT "18888"
#define MAXCLIENTS 4

int main(void) {
	int closeServer = 1;
	Server myServer(MAXCLIENTS, (char *) PORT);
	std::cout << "Starting server thread...\n";
	std::thread serverThread = myServer.spawn();

	std::cout << "To close the server enter 0: ";
	while (closeServer)
		std::cin >> closeServer;
	serverThread.detach();
	return 0;
}