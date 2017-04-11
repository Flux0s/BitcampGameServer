#ifndef GAME_H
#define GAME_H

#include <thread>
#include <queue>
#include "Client.h"
#include "Request.h"

class Game {
public:
	Game();

	Game(int, Client *);

	void addRequest(Request);

	void startGame();

	bool isRunning();

	void killGame();

private:
	void run();

	bool m_isRunning, m_killGame;
	int m_numPlayers;
	Client *m_clients;
	std::queue<Request> m_requests;
};

#endif