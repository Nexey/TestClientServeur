#include <iostream>
#include "../Exceptions/Erreur.h"
#include "MaWinsock.h"

/* static */ MaWinsock * MaWinsock::instanceUnique = NULL;

/* static */ MaWinsock * MaWinsock::getInstance() {
	if (!instanceUnique) instanceUnique = new MaWinsock;
	return instanceUnique;
}

MaWinsock::MaWinsock(void) {
	int r = WSAStartup(MAKEWORD(2, 0), &wsaData);

	if (r) throw Erreur("Initialisation Winsock incompl�te");
	std::cout << "Initialisation Winsock compl�te" << std::endl;
}

MaWinsock::~MaWinsock(void) {
	WSACleanup();
}