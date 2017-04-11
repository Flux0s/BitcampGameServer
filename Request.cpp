#include "Request.h"

Request::Request() {}

Request::Request(int playerNum, void *byteStream, int streamLength) {
	m_player = playerNum;
}
