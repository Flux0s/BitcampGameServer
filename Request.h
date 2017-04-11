#ifndef BITCAMP_REQUEST_H
#define BITCAMP_REQUEST_H

class Request {
public:
	Request();

	Request(int, void *, int);

private:
	int m_player;
};

#endif