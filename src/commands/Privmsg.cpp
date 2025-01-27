
#include "Privmsg.hpp"

Privmsg::~Privmsg( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Privmsg::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "PRIVMSG  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
