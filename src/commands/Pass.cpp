
#include "Pass.hpp"

Pass::~Pass( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Pass::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "PASS  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}