#pragma once
class Client;

class IVisiteur {
public :
	virtual bool visite(Client*) = 0;
};