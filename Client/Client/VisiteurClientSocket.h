#pragma once
#include "IVisiteur.h"

class VisiteurClientSocket :
	public IVisiteur {
public :
	bool visite(Client* client);
};

