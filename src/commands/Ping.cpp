
#include "Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

/*
void Ping::execute( void )
{
	std::cout << "PING => TODO" << std::endl;
}
*/

void Ping::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "PING  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}