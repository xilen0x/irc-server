
#include "User.hpp"

User::~User( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void User::execute( std::string msg )
{
	std::cout << "    ----" << std::endl;
	std::cout << "USER  => TODO with message " << msg << std::endl;
	std::cout << "    ----" << std::endl;
}
