
#include "Join.hpp"

Join::~Join( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Join::execute( std::string &msg, int fd )
{
	(void)fd;
	std::cout << "    ----" << std::endl;
	std::cout << "JOIN  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
