
#include "Cap.hpp"

void Cap::execute( Server* server, std::string &msg, int fd )
{
	(void)msg;
	(void)server;
	
	send(fd, "CAP * LS :\r\n", 12, 0);//empty CAP LS
}

Cap::~Cap( void ) {};
