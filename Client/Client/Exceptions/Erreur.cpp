#include "Erreur.h"

/**
mise en oeuvre de la classe Erreur
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include "Erreur.h"

Erreur::Erreur() {
	strcpy_s(this->message, "Erreur !");
}

Erreur::Erreur(const char * messageErreur) {
	strcpy_s(this->message, "Erreur : ");
	int l = strlen(messageErreur);
	static int n = LONGUEURMESSAGE - 9;
	if (l <= n) strcat_s(this->message, messageErreur);
	else {
		strncat_s(this->message, messageErreur, n);
		this->message[LONGUEURMESSAGE] = '\0';
	}
}

Erreur::~Erreur() {}

Erreur::operator std::string() const {
	return std::string(this->message);
}

std::ostream & operator << (std::ostream & os, const Erreur & erreur) {
	os << (std::string)erreur;
	return os;
}