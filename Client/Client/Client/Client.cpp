/*
 * ClientDessin.cpp
 *
 *  Created on: 26 août 2014
 *      Author: Dominique
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Client.h"
#include <sstream>
#include "../Exceptions/Erreur.h"

Client::Client(const std::string & adresseServeur, const int portServeur) {
	MaWinsock::getInstance();	// initialisation de la DLL : effectuée une seule fois
	this->adresseServeur = adresseServeur;
	this->portServeur = portServeur;

	//---------------------- création socket -------------------------------------------------

	int r;

	int familleAdresses = AF_INET;         // IPv4
	int typeSocket = SOCK_STREAM;           // mode connecté TCP
	int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers paramètres
											// pour les valeurs des paramètres : cf. fct socket dans la doc sur winsock

	// sock = socket(familleAdresses, typeSocket, protocole);
	sock = socket(familleAdresses, typeSocket, 0);

	if (sock == INVALID_SOCKET) {
		std::ostringstream oss;
		oss << "La création du socket a échoué : code d'erreur = " << WSAGetLastError() << std::endl;	// pour les valeurs renvoyées par WSAGetLastError() : cf. doc réf winsock
		throw Erreur(oss.str().c_str());
	}

	std::cout << "Socket créé" << std::endl;

	//------------------------------ création du représentant du serveur ----------------------------------------

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(adresseServeur.c_str());   // inet_addr() convertit de l'ASCII en entier
	sockaddr.sin_port = htons((short)portServeur);                 //htons() assure que le port est bien inscrit dans le format du réseau (little-endian ou big-endian)

	//-------------- connexion du client au serveur ---------------------------------------

	do {
		std::cout << "Test de connexion" << std::endl;
		r = connect(sock, (SOCKADDR *)&sockaddr, sizeof(sockaddr));     // renvoie une valeur non nulle en cas d'échec.
																		// Le code d'erreur peut être obtenu par un appel à WSAGetLastError()

		if (WSAGetLastError() != 0) std::cout << "Retentative de connexion" << std::endl;
	} while (r == SOCKET_ERROR);

	std::cout << "Connexion au serveur réussie" << std::endl;
}

Client::~Client() {
	int r = shutdown(sock, SD_BOTH);					// on coupe la connexion pour l'envoi et la réception
														// renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()

	if (r == SOCKET_ERROR)
		std::cerr << "La coupure de connexion a échoué";

	r = closesocket(sock);                          // renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()
	if (r) std::cerr << "La fermeture du socket a échoué";

	std::cout << "Arrêt normal du client" << std::endl;
}

/* Remplacée par un visiteur 
void Client::sendSocket(const std::string & req) {
	int r;
	r = send(sock, req.c_str(), (int)req.length(), 0);             //------------------ envoi de la requête au serveur -------------------------------

	if (r == SOCKET_ERROR)
		throw Erreur("Échec de l'envoi de la requête");

	std::cout << "Requête envoyée au serveur" << std::endl;
}
*/
bool Client::accepte(IVisiteur* visiteur) {
	return visiteur->visite(this);
}
