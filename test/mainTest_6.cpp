#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

std::string			nick_1="nick_1";
std::string			nick_2="nick_2";
std::string			nick_3="nick_3";
std::string			nick_4="nick_4";

int main()
{
	Messageprocessing	messageProcesing;
	Client				client(-1, "IP_CLIENTE");
	Server				server("42_IRC", "hola", 4444);
	Channel				channel1("channel_1", nick_1);

    std::cout << "\n!!!!!!  TEST  Server : Add client and channel1 !!!!!!!\n" << std::endl;

    std::cout << "\n-- Add client and channel1---" << std::endl;
	server.addClient(client);
	server.addChannel(channel1);
    std::cout << "-- End Add client and channel1---\n" << std::endl;

    return (0);

}
