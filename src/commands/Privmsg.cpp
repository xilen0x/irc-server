
#include "Privmsg.hpp"

Privmsg::~Privmsg( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Privmsg::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "    ----" << std::endl;
		std::cout << "PRIVMSG  => TODO wit message " << msg << std::endl;
		std::cout << "    ----" << std::endl;
	}
}