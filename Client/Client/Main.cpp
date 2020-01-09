// #include <Windows.h> // Pour les accents dans la console sous Windows

#include "./Client/Client.h"
#include "./Exceptions/Erreur.h"
#include "./VisiteurClientSocket.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv) {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows

	Client client("127.0.0.16", 10000);
	IVisiteur * visiteur = new VisiteurClientSocket();
	bool continuer = true;
	while (continuer = client.accepte(visiteur));
}