
#include "Nick.hpp"

Nick::~Nick( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Nick::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "NICK  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
