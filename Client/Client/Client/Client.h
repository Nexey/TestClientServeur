#pragma once
/*
 * ClientDessin.h
 *
 *  Created on: 26 août 2014
 *      Author: Dominique
 */

#include <string>
#include <string.h>
#include "MaWinsock.h"

class Client {
	SOCKET sock;  // informations concernant le socket à créer : famille d'adresses acceptées, mode connecté ou non, protocole 
	SOCKADDR_IN sockaddr; // informations concernant le serveur avec lequel on va communiquer
	std::string adresseServeur;
	int portServeur;
public:
	Client(const std::string & adresseServeur, const int portServeur);
	~Client();

	void sendSocket(const std::string& req);
};