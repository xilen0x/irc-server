#include <string>
#include "Server.hpp"
#include "replies.hpp"

/* Doesn´t check wrong parameter
 * returns:
 * 	- true : No errors
 *  - false: errors and error is sent to fd
 */

bool extractParams(Server* server, std::string command, std::string &msg, int fd)
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
