#ifndef GAME_H
#define GAME_H

#include "Client.h"

class Game {
public:
	Game();

	Game(int, Client *);

private:
	int m_numPlayers;
	Client *m_clients;

};

#endif
