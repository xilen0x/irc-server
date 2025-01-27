
#include "Topic.hpp"

Topic::~Topic( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Topic::execute( std::string &msg, int fd )
{
	(void)fd;
	std::cout << "    ----" << std::endl;
	std::cout << "TOPIC  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
