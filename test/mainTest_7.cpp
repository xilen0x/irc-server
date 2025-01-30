#include <iostream>
#include <sstream>
#include <string>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

# define MAX_NUMBER 6
# define BASE_IP_NAME "IP_CLIENT"
# define BASE_NICK "nick_"
# define BASE_CHANNEL_NAME "channel_"

std::string			nick_1="nick_1";
std::string			nick_2="nick_2";
std::string			nick_3="nick_3";
std::string			nick_4="nick_4";

void	addClientsChannels ( Server & server)
{
	std::string	numStr;

    std::cout << "\n--- Add several clients and channels ---" << std::endl;
	for (int i=3; i <= MAX_NUMBER; i++)
	{
		std::ostringstream	str1;

		str1 << i;
		numStr = str1.str();

		std::cout << "\n-- i=" << i << " START ---"<< std::endl;

		Client	client(i, BASE_IP_NAME + numStr);
		Channel channel(BASE_CHANNEL_NAME + numStr,  BASE_NICK + numStr);
	
		std::cout << "  - START ADD ---"<< std::endl;
		server.addClient(client);
		server.addChannel(channel);

		std::cout << "   -END  ADD ---"<< std::endl;

		std::cout << "    - Client => _fd=" << client.getFdClient() << ", _ip=" << client.getIpClient() << std::endl;
		std::cout << "    - Channel => _channelName=" << channel.getChannelName() << std::endl;
		std::cout << "-- i=" << i << " END ---\n"<< std::endl;
	}

/*
 * Todo añadr nicks en cada channel
 
		addMember("Uno");
		addMember("Dos");
		addMember("Tres");
*/
    std::cout << "-- End several clients and channels ---\n" << std::endl;
}

void printClientChannels( Server & server )
{
    std::vector<Client>		clients;
	std::vector<Channel>	channels;

	clients = server.getClients();
	channels = server.getChannels();

    std::cout << "\n--- PRINT clients and channels ---" << std::endl;
	for (unsigned long i=0; i < clients.size(); i++)
	{
		std::cout << "- Client => fd=" << clients[i].getFdClient() << ", _ip=" << clients[i].getIpClient() << std::endl;
		std::cout << "- Channel => channelName=" << channels[i].getChannelName() << std::endl;
		channels[i].printChannelVars();
		std::cout << std::endl;
	}
    std::cout << "-- END print clients and channels ---\n" << std::endl;

	channels[0].printChannelVars();
}

int main()
{
	Messageprocessing	messageProcesing;
//	Client				client(-1, BASE_IP_NAME); 
	Server 				server("42_IRC", "hola", 4444);
//	Channel				channel1("channel_1", nick_1);

    std::cout << "\n!!!!!!  TEST 7 Server : Add several clients and channels !!!!!!!\n" << std::endl;

	addClientsChannels( server );
	printClientChannels( server );
    return (0);

}
