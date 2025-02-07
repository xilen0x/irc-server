
#include "Mode.hpp"

Mode::~Mode( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Mode::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "MODE  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
