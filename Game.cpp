#include "Game.h"

Game::Game() {}

Game::Game(int numPlayers, Client *players) {
	m_killGame = false;
	m_isRunning = false;
	m_numPlayers = numPlayers;
	m_players = players;
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
	notifyAllPlayers("Starting game...");
	while (m_killGame == false && gameover == false) {
		//TODO: send clients messages that confirm server has received their data

	}
	notifyAllPlayers("Game has ended!");
}

bool Game::isRunning() {
	return (m_isRunning);
}

//TODO: notify clients that the game has been closed unexpectedly
void Game::killGame() {
	notifyAllPlayers("Game has been ended unexpectedly!");
	m_killGame = true;
}

void Game::notifyAllPlayers(std::string message) {
	for (int i = 0; i < m_numPlayers; i++) {
		m_players[i].send(message.c_str());
	}
}

Game::~Game() {
	if (m_isRunning)
		killGame();
	notifyAllPlayers("Server is closing!");
}
