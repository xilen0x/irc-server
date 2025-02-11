
#include "Ping.hpp"

Ping::~Ping( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Ping::execute( Server* server, std::string &msg , int fd)
{
	//The next lines from 11 to 21 are equal to PASS (changue in line 19 where here is PING)
    msg = trimLeft(msg);
    msg = msg.substr(4);
    msg = trimLeft(msg);

    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), "PING"), fd);  // 461
        return;
    }

	server->sendResp(PONG(msg),fd);
}
