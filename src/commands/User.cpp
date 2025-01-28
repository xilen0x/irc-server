
#include "User.hpp"

User::~User( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void User::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "USER  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
