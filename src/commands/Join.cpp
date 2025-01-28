
#include "Join.hpp"

Join::~Join( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Join::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)msg;
	// std::cout << "    ----" << std::endl;
	// std::cout << "JOIN  => TODO with message " << msg << std::endl;
	// std::cout << "    ----" << std::endl;

	std::cout << "getChannels: " << server->getChannels().size() << std::endl;
	std::cout << "getClients:" << server->getClients().size() << std::endl;
	for (unsigned long i=0; i < server->getClients().size(); i++)
	{
		std::cout << "getFD[" << i << "]:" << server->getClients()[i].getFdClient() << std::endl;
	}
}
