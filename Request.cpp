#include "Request.h"

Request::Request() {}

Request::Request(int playerNum, void *byteStream, int streamLength) {
	m_playerNum = playerNum;
}

int Request::getPlayerNum() {
	return (m_playerNum);
}
