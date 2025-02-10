
#include "Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Ping::execute( Server* server, std::string &msg , int fd)
{
	//TODO extract ping and spaces after ping and send the rest of message
	server->sendResp(PONG(msg),fd);
}
