#include "Game.h"

Game::Game() {}

Game::Game(int numPlayers, Client *players) {
	m_isRunning = false;
	m_numPlayers = numPlayers;
	m_clients = players;
}

void Game::addRequest(Request newRequest) {
	m_requests.push(newRequest);
}
