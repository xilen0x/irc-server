
#include "Mode.hpp"

Mode::~Mode( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Mode::execute( Server* server, std::string &msg , int fd)
{
		if (isAuthenticated(server->getClient(fd), server, fd))
		{
			std::cout << "    ----" << std::endl;
			std::cout << "MODE  => TODO with message " << msg << std::endl;
			std::cout << "    ----" << std::endl;
		}
}
