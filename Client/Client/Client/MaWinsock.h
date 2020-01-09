#pragma once
#include <WinSock2.h>
class Erreur;

class MaWinsock {
	WSADATA wsaData;
	MaWinsock(void);

	static MaWinsock * instanceUnique;
public:
	static MaWinsock * getInstance();
	~MaWinsock(void);
};