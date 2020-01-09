// #include <Windows.h> // Pour les accents dans la console sous Windows

#include "./Client/Client.h"
#include "./Exceptions/Erreur.h"

#pragma comment(lib, "Ws2_32.lib")


int main(int argc, char **argv) {
	SetConsoleOutputCP(1252); // Pour les accents dans la console sous Windows

	Client client("127.0.0.16", 10000);
	std::string Message = "";

	std::cout << "Écrivez un message : ";
	std::getline(std::cin, Message);
	std::cout << std::endl;

	Message += "\n";
	client.sendSocket(Message);

	std::cout << "Écrivez un message : ";
	std::getline(std::cin, Message);
	std::cout << std::endl;

	Message += "\n";
	client.sendSocket(Message);

	std::cout << "Écrivez un message : ";
	std::getline(std::cin, Message);
	std::cout << std::endl;

	Message += "\n";
	client.sendSocket(Message);
}