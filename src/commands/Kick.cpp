
#include "Kick.hpp"

Kick::~Kick( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Kick::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "KICK  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
