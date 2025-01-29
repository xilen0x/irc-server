
#include "Quit.hpp"

Quit::~Quit( void ) {};

/* ------------------- PUBLIC MEMBER FUNCTIONS ------------------*/

void Quit::execute( Server* server, std::string &msg , int fd)
{
	std::vector<std::string> splitedStrVect;

	std::string nick = "nickTest";
	std::string user = "userName";
//	(void)fd;
//	(void)server;

	std::cout << "    ----" << std::endl;
	std::cout << "QUIT  => TODO test bad format" << std::endl;
	deleteRN(msg);
	splitedStrVect = splitByDoublePoint(msg);
	if (splitedStrVect.size() == 2)
		server->sendResp(MSG_QUIT_CHANNEL_REASON(nick, user, splitedStrVect[1]), fd);
	else
		server->sendResp(MSG_QUIT_CHANNEL_NO_REASON(nick, user), fd);
	std::cout << "    ----" << std::endl;
}
