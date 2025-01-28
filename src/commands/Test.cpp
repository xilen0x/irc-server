
#include "Test.hpp"
#include <sstream>
#include <sys/socket.h>

Test::~Test( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Test::execute( Server* server, std::string &msg, int fd )
{
	// (void)msg;
	// (void)fd;
	(void)server;
	// std::cout << "Test command executed" << std::endl;

	std::stringstream stream;
	stream << ":localhost " << "88888" << " " << "clientname " << msg << fd << "\r\n";
	std::string resp = stream.str();
	if(send(fd, resp.c_str(), resp.size(),0) == -1)
		std::cerr << "send failed" << std::endl;
}


