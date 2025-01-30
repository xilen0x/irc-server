
#include "Cap.hpp"

Cap::~Cap( void ) {};

void Cap::execute( Server* server, std::string &msg, int fd )
{
	(void)msg;
	(void)server;
	// (void)fd;
	// send(fd, "CAP * LS :\r\n", 12, 0); 
	send(fd, "CAP * LS :multi-prefix\r\n", 24, 0);//Permite ver múltiples prefijos de usuario (@%+).
	// std::cout << "Cap command executed" << std::endl;
}
