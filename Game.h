#ifndef GAME_H
#define GAME_H

#include <queue>
#include "Client.h"
#include "Request.h"

class Game {
public:
	Game();

	Game(int, Client *);

	void addRequest(Request);

private:
	bool m_isRunning;
	int m_numPlayers;
	Client *m_clients;
	std::queue<Request> m_requests;
};

#endif
