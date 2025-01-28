
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}