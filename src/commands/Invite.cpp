
#include "Invite.hpp"
#include "irc.hpp"

Invite::~Invite( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Invite::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "    ----" << std::endl;
		std::cout << "INVITE  => TODO wit message " << msg << std::endl;
		std::cout << "    ----" << std::endl;
	}
}
