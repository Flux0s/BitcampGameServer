#include "Game.h"

Game::Game() {}

Game::Game(int numPlayers, Client *players) {
	m_numPlayers = numPlayers;
	m_clients = players;
}