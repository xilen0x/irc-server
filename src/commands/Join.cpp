
#include <sstream>

#include "Join.hpp"

#define MY_CHANNEL_NAME "MyChannel"
#define BASE_NICK "nick_"
#define BASE_USER_NAME "userName_"

Join::~Join( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Join::execute( Server* server, std::string &msg , int fd)
{
	std::vector<Client> clients = server->getClients();
	std::vector<Channel> channels = server->getChannels();
	std::string	numStr;
	std::string	nick;
	(void)fd;
	(void)msg;
	// std::cout << "    ----" << std::endl;
	// std::cout << "JOIN  => TODO with message " << msg << std::endl;
	// std::cout << "    ----" << std::endl;

	std::cout << "getChannels: " << channels.size() << std::endl;
	std::cout << "getClients:" << clients.size() << std::endl;

	for (unsigned long i=0; i < clients.size(); i++)
	{
		std::cout << "- getFD[" << i << "]:" << clients[i].getFdClient() << std::endl;
	}

	// Add nick and user on client 	
	Client	*client;
	Channel	*channel;

	client = server->getClientByFD(fd);
	if (client != NULL)
	{
/*
		std::ostringstream	str1;

		str1 << fd;
		numStr = str1.str();

		nick = BASE_NICK + numStr;
		client->setNick(nick);
		client->setUserName(nick);
		std::cout << " added : " << client->getNick() << std::endl;
*/
		nick = client->getNick();
		if (channels.size() == 0)
		{
			Channel newChannel(MY_CHANNEL_NAME, nick);
	//		newChannel.printChannelVars();
			server->addChannel(newChannel);
			std::cout << "Channels size = " << server->getChannels().size() << std::endl;
		}
		else
		{
			channel = server->getChannelsByNumPosInVector(0);
 			channel->addMember(nick);
			std::cout << "- Nick added " << nick << std::endl;
			std::cout << "-  " << nick << " is added as member? " << server->getChannels()[0].isMember(nick) << std::endl;
		}
		if ( server->getChannels().size() > 0)
		{
			channel = server->getChannelsByNumPosInVector(0);
			channel->printChannelVars();
		}
		else
			std::cout << "ERROR : no channels" << std::endl;
	}
}
