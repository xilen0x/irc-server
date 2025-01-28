
#include "Test.hpp"

Test::~Test( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Test::execute( std::string &msg, int fd )
{
	(void)msg;
	(void)fd;
	std::cout << "Test command executed" << std::endl;
}
