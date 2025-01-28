
#include "Nick.hpp"

Nick::~Nick( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Nick::execute( std::string &msg, int fd )
{
	(void)fd;
	std::cout << "    ----" << std::endl;
	std::cout << "NICK  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
