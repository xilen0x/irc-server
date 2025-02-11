
#include "Test.hpp"
#include <sstream>
#include <sys/socket.h>

Test::~Test( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Test::execute( Server* server, std::string &msg, int fd )
{
		std::cout << "TEST" << msg << std::endl;
}

