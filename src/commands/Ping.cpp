
#include "Ping.hpp"

Ping::~Ping( void ) {}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
// Doesn´t check wrong parameter
void Ping::execute( Server* server, std::string &msg , int fd)
{
	if (extractParams(server, "PING", msg, fd))
		server->sendResp(PONG(msg),fd);
}
