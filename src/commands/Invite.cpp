
#include "Invite.hpp"

Invite::~Invite( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Invite::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "INVITE  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
