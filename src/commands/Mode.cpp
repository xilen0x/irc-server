
#include "Mode.hpp"

Mode::~Mode( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Mode::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "MODE  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
