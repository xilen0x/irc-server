
#include "Topic.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( Server* server, std::string &msg , int fd)
{
	if (isAuthenticated(server->getClient(fd), server, fd))
	{
		std::cout << "    ----" << std::endl;
		std::cout << "TOPIC  => TODO with message " << msg << std::endl;
		std::cout << "    ----" << std::endl;
	}
}
