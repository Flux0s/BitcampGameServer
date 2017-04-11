#include "Game.h"

Game::Game() {
	m_isRunning = false;
	m_clients = NULL;
	m_numPlayers = 0;
}

Game::Game(int numPlayers, Client *players) {
	m_numPlayers = numPlayers;
	m_clients = players;
}

void Game::addRequest(Request newRequest) {
	m_requests.push(newRequest);
}
