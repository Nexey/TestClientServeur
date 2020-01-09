#pragma once
/**
classe Erreur
*/

#include <string>
#include <iostream>

class Erreur {
public:
	const static int LONGUEURMESSAGE = 500;
	char message[1 + LONGUEURMESSAGE];
	Erreur();
	Erreur(const char * messageErreur);

	virtual ~Erreur();
	operator std::string() const;
};

std::ostream & operator << (std::ostream & os, const Erreur & erreur);