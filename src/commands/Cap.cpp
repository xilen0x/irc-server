
#include "Cap.hpp"

void Cap::execute( Server* server, std::string &msg, int fd )
{
	(void)msg;
	(void)server;
	// (void)fd;
	send(fd, "CAP * LS :\r\n", 12, 0);            //empty CAP LS
	// send(fd, "CAP * LS :multi-prefix\r\n", 24, 0);//Permite ver múltiples prefijos de usuario (@%+).
	// std::cout << YEL << "Cap command executed" << RES << std::endl;
}

Cap::~Cap( void ) {};
