#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

void testClient(Client & client)
{
	client.printClientVars();
}

int main()
{
	std::string			nick_1="nick_1";

	Messageprocessing	messageProcesing;
	Client				client(-1, "IP_CLIENTE");
	Server				server("42_IRC", "hola", 4444);
	Channel				channel1("channel_1", nick_1);

    std::cout << "Executing Messageprocessing !" << std::endl;

	messageProcesing.processMessage("tokenPing!!");

	testClient(client);

    return (0);
}
