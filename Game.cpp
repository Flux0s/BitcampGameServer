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
	//TODO: Move this thread ouside so the entire class is a thread
	std::thread gameThread(&Game::run, Game());
}

void Game::run() {
	bool gameover = false;
	m_isRunning = true;
	notifyAllPlayers("Starting game...");
	while (m_killGame == false && gameover == false) {
		if (m_requests.size() > 0) {
			m_players[m_requests.front().getPlayerNum() - 1].send("Request received and handled.");
			m_requests.pop();
		}
	}
	m_isRunning = false;
	notifyAllPlayers("Game has ended!");
}

bool Game::isRunning() {
	return (m_isRunning);
}

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
