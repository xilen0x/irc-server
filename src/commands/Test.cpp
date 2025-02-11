
#include "Test.hpp"
#include <sstream>
#include <sys/socket.h>

Test::~Test( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Test::execute( Server* server, std::string &msg, int fd )
{
	(void)server;
	(void)fd;
	std::cout << "TEST command: " << msg << std::endl;
}

