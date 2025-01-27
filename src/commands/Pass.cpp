
#include "Pass.hpp"

Pass::~Pass( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Pass::execute( std::string &msg, int fd )
{
	(void)fd;
	std::cout << "    ----" << std::endl;
	std::cout << "PASS  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
