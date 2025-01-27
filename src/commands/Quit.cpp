
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
