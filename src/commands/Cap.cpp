
#include "Cap.hpp"

Cap::~Cap( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Cap::execute( std::string &msg, int fd )
{
	std::cout << "    ----" << std::endl;
	std::cout << "CAP  => TODO with fd=" << fd << " and  message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
