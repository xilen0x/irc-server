#include <iostream>
#include "../inc/Client.hpp"
#include "../inc/Messageprocessing.hpp"
#include "../inc/Server.hpp"

int main()
{
	Messageprocessing	messageProcesing;
	Client				client(-1, "IP_CLIENTE");
	Server				server("42_IRC", "hola", 4444);


    std::cout << "Executing Messageprocessing !" << std::endl;

	messageProcesing.processMessage("tokenPing!!");
    return (0);
}
