#ifndef GAME_H
#define GAME_H

#include <thread>
#include <queue>
#include <iostream>
#include <mutex>

#include "Client.h"
#include "Request.h"

#define MINPLAYERS 2

class Game {
public:
	Game();

	Game(int, Client *);

	void addRequest(Request);

	bool isRunning();

	std::thread spawn();

	void killGame();

	~Game();

private:
	void run();

	void notifyAllPlayers(std::string);

	bool m_isRunning, m_killGame;
	int m_numPlayers;
	Client *m_players;
	std::queue<Request> m_requests;
	std::mutex m_mutex;
};

#endif