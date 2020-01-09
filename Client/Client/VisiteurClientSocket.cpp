#include "VisiteurClientSocket.h"
#include <iostream>
#include "./Exceptions/Erreur.h"
#include "./Client/Client.h"


bool VisiteurClientSocket::visite(Client* client) {
	std::string req = "";

	std::cout << "�crivez un message : ";
	std::getline(std::cin, req);
	std::cout << std::endl;

	if (req == "") return false;

	req += "\n";

	int r;
	r = send(client->sock, req.c_str(), (int)req.length(), 0);             //------------------ envoi de la requ�te au serveur -------------------------------

	if (r == SOCKET_ERROR)
		throw Erreur("�chec de l'envoi de la requ�te");

	std::cout << "Requ�te envoy�e au serveur" << std::endl;
	return true;
}
