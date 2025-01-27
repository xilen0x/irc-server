
#include "Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

// void Ping::execute( void )
// {
// 	std::cout << "PING => TODO" << std::endl;
// }

void Ping::execute( std::string token )
{
	std::cout << "    ----" << std::endl;
	std::cout << "PING responde en la siguiente linea con:" << std::endl;
	std::cout << PONG(token) << std::endl;
	std::cout << "    ----" << std::endl;
}
