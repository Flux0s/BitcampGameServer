#include "Game.h"

Game::Game() {
	m_numPlayers = 0;
}

Game::Game(int numPlayers, Client *players) {
	m_killGame = false;
	m_isRunning = false;
	m_numPlayers = numPlayers;
	m_players = players;
}

void Game::addRequest(Request newRequest) {
	m_requests.push(newRequest);
}

std::thread Game::spawn() {
	return (std::thread([this] { run(); }));

}

void Game::run() {
	bool gameover = false;
	m_isRunning = true;
	notifyAllPlayers("Starting game...");
	while (!m_killGame && !gameover) {
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
	std::lock_guard<std::mutex> guard(m_mutex);
	notifyAllPlayers("Closing game unexpectedly!");
	m_killGame = true;
}

void Game::notifyAllPlayers(std::string message) {
	for (int i = 0; i < m_numPlayers; i++) {
		m_players[i].send(message.c_str());
	}
}

Game::~Game() {
	if (m_isRunning) {
		killGame();
	}
}