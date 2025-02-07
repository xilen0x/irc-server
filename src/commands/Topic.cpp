
#include "Topic.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( Server* server, std::string &msg , int fd)
{
	(void)fd;
	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "TOPIC  => TODO wit message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
