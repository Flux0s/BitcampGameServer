#include "Game.h"

Game::Game() {}

Game::Game(int numPlayers, Client *players) {
	m_killGame = false;
	m_isRunning = false;
	m_numPlayers = numPlayers;
	m_clients = players;
}

void Game::addRequest(Request newRequest) {
	m_requests.push(newRequest);
}

void Game::startGame() {
	std::thread gameThread(run());
}

void Game::run() {
	bool gameover = false;
	m_isRunning = true;
	while (m_killGame == false && gameover == false) {
		//TODO: send all clients messages that confirm server has received their data
		usleep(10000);
	}
}

bool Game::isRunning() {
	return (m_isRunning);
}

//TODO: notify clients that the game has been closed unexpectedly
void Game::killGame() {
	m_killGame = true;
}