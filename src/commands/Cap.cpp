
#include "Cap.hpp"

Cap::~Cap( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Cap::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "CAP  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
