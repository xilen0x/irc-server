
#include "Cap.hpp"

Cap::~Cap( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

// void Cap::execute( std::string &msg, int fd )
void Cap::execute( Server* server, std::string &msg, int fd )
{
	(void)server;
	(void)fd;

	std::cout << "    ----" << std::endl;
	std::cout << "CAP  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
