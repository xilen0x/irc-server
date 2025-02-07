
#include "Kick.hpp"

Kick::~Kick( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Kick::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	// (void)msg;
	(void)server;
	std::cout << "    ----" << std::endl;
	std::cout << "KICK  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
