
#include "Ping.hpp"

Ping::~Ping( void ) {}

/* ------------------- PRIVATE FUNCTIONS ------------------*/

/* Doesn´t check wrong parameter
 * returns:
 * true : No errors
 * false: errors and error is sent to fd
 */

bool Ping::_extractParams(Server* server, std::string command, std::string &msg, int fd)
{
    msg = trimLeft(msg);
    msg = msg.substr(command.size());
    msg = trimLeft(msg);

    if (!msg.empty() && msg[0] == ':')
        msg = msg.substr(1);
    if (msg.empty())
    {
        server->sendResp(ERR_NEEDMOREPARAMS(std::string("*"), command), fd);  // 461  //Perhaps "*" must be changed
        return (false);
    }
	return(true);
}

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/
// Doesn´t check wrong parameter
void Ping::execute( Server* server, std::string &msg , int fd)
{
	if (_extractParams(server, "PING", msg, fd))
		server->sendResp(PONG(msg),fd);
}
