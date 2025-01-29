
#include <sstream>

#include "Join.hpp"

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
		std::cout << "getFD[" << i << "]:" << clients[i].getFdClient() << std::endl;
	}
	
	for (unsigned long i = 0; i < clients.size(); i++)
	{
		if (clients[i].getFdClient() == fd)
		{
			std::ostringstream	str1;

			str1 << i;
			numStr = str1.str();

			nick = BASE_NICK + numStr;
			clients[i].setNick(nick);
			clients[i].setUserName(nick);
			break;
		}
	}

	if (channels.size() == 0)
	{
		Channel newChannel("MyChannel", nick);
		server->addChannel(newChannel);
	}
	else
		channels[0].addMember(nick);
	if ( channels.size() > 0 )
		channels[0].printChannelVars();
	else
		std::cout << "ERROR : no channels" << std::endl;
}
