#include "VisiteurClientSocket.h"
#include <iostream>
#include "./Exceptions/Erreur.h"
#include "./Client/Client.h"


bool VisiteurClientSocket::visite(Client* client) {
	std::string req = "";

	std::cout << "Écrivez un message : ";
	std::getline(std::cin, req);
	std::cout << std::endl;

	if (req == "") return false;

	req += "\n";

	int r;
	r = send(client->sock, req.c_str(), (int)req.length(), 0);             //------------------ envoi de la requête au serveur -------------------------------

	if (r == SOCKET_ERROR)
		throw Erreur("Échec de l'envoi de la requête");

	std::cout << "Requête envoyée au serveur" << std::endl;
	return true;
}
