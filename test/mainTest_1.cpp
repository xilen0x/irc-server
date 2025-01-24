#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

int main()
{
	Messageprocessing	messageProcesing;
	Client				client(-1, "IP_CLIENTE");
	Server				server("42_IRC", "hola", 4444);
	Channel				channel1("channel_1", "nick_1");

    std::cout << "\n!!!!!!!!!!!!!!!!  TODO  main() !!!!!!\n" << std::endl;

    return (0);
}
