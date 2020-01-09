/*
 * ClientDessin.cpp
 *
 *  Created on: 26 ao�t 2014
 *      Author: Dominique
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Client.h"
#include <sstream>
#include "../Exceptions/Erreur.h"

Client::Client(const std::string & adresseServeur, const int portServeur) {
	MaWinsock::getInstance();	// initialisation de la DLL : effectu�e une seule fois
	this->adresseServeur = adresseServeur;
	this->portServeur = portServeur;

	//---------------------- cr�ation socket -------------------------------------------------

	int r;

	int familleAdresses = AF_INET;         // IPv4
	int typeSocket = SOCK_STREAM;           // mode connect� TCP
	int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers param�tres
											// pour les valeurs des param�tres : cf. fct socket dans la doc sur winsock

	// sock = socket(familleAdresses, typeSocket, protocole);
	sock = socket(familleAdresses, typeSocket, 0);

	if (sock == INVALID_SOCKET) {
		std::ostringstream oss;
		oss << "La cr�ation du socket a �chou� : code d'erreur = " << WSAGetLastError() << std::endl;	// pour les valeurs renvoy�es par WSAGetLastError() : cf. doc r�f winsock
		throw Erreur(oss.str().c_str());
	}

	std::cout << "Socket cr��e" << std::endl;

	//------------------------------ cr�ation du repr�sentant du serveur ----------------------------------------

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(adresseServeur.c_str());   // inet_addr() convertit de l'ASCII en entier
	sockaddr.sin_port = htons((short)portServeur);                 //htons() assure que le port est bien inscrit dans le format du r�seau (little-endian ou big-endian)

	//-------------- connexion du client au serveur ---------------------------------------

	do {
		std::cout << "Test de connexion" << std::endl;
		r = connect(sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr));     // renvoie une valeur non nulle en cas d'�chec.
																		// Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()

		if (WSAGetLastError() != 0) std::cout << "Retentative de connexion" << std::endl;
	} while (r == SOCKET_ERROR);

	std::cout << "Connexion au serveur r�ussie" << std::endl;
}

Client::~Client() {
	int r = shutdown(sock, SD_BOTH);					// on coupe la connexion pour l'envoi et la r�ception
														// renvoie une valeur non nulle en cas d'�chec. Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()

	if (r == SOCKET_ERROR)
		std::cerr << "La coupure de connexion a �chou�";

	r = closesocket(sock);                          // renvoie une valeur non nulle en cas d'�chec. Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()
	if (r) std::cerr << "La fermeture du socket a �chou�";

	std::cout << "Arr�t normal du client" << std::endl;
}

bool Client::accepte(IVisiteur* visiteur) {
	return visiteur->visite(this);
}
