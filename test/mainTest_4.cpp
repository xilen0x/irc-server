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

    std::cout << "\n TEST  Channel modification Member and Invited\n" << std::endl;

	channel1.printChannelVars();

	channel1.addMember(nick_2);
	channel1.addInvited(nick_3);
	channel1.addInvited(nick_4);
	channel1.addInvited(nick_3);

	channel1.printChannelVars();

    return (0);
}
